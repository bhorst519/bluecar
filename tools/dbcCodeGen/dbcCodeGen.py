import argparse, json, os, re
from render import Render
from helpers import *

#---------------------------------------------------------------------------------------------------
# Class for code generation management
#---------------------------------------------------------------------------------------------------
class DbcCodeGen:
    def __init__(self, dbcFilePath, rxFilePath, generatedCodeDirPath, alias, node, genDebugFiles):
        self.generatedCodeDirPath = generatedCodeDirPath
        self.alias = alias
        self.node = node
        self.genDebugFiles = genDebugFiles
        self.rxExpressions = [".*"]

        self.dbcFileHandle = open(dbcFilePath, "r")
        if not os.path.exists(generatedCodeDirPath):
            os.mkdir(generatedCodeDirPath)

        if rxFilePath is not None:
            with open(rxFilePath, "r") as rxFileHandle:
                self.rxExpressions = json.load(rxFileHandle)
        if type(self.rxExpressions) is not list:
            raise Exception(f"RX file {rxFilePath} is not a list of regex expressions")

        if genDebugFiles:
            signalInfoFile = os.path.join(generatedCodeDirPath, f"{alias}_signals.txt")
            messageInfoFile = os.path.join(generatedCodeDirPath, f"{alias}_messages.txt")
            self.signalInfoFileHandle = open(signalInfoFile, "w")
            self.messageInfoFileHandle = open(messageInfoFile, "w")


    def Finish(self):
        self.dbcFileHandle.close()

        if self.genDebugFiles:
            self.signalInfoFileHandle.close()
            self.messageInfoFileHandle.close()


    def Run(self):
        # Parse DBC file for message and signal info
        inMessage = None
        messageInfo = []
        messageIds = []  # Order must align with that of messageInfo
        signalInfo = []
        signalNames = []  # Order must align with that of signalInfo
        for idx, line in enumerate(self.dbcFileHandle):
            regexMessageStart = re.search(RE_SEARCH_MESSAGE_START, line)
            regexSignalInfo = re.search(RE_SEARCH_SIGNAL_INFO, line)
            regexSignalValTableInfo = re.search(RE_SEARCH_SIGNAL_VAL_TABLE_INFO, line)
            regexMessageCycleTimeInfo = re.search(RE_SEARCH_SIGNAL_MSG_CYCLE_TIME_INFO, line)

            if regexMessageStart is not None:
                thisMessageInfo = GetMessageInfo(regexMessageStart)
                messageInfo += [thisMessageInfo]
                messageIds += [thisMessageInfo["id"]]
                inMessage = [thisMessageInfo["name"], thisMessageInfo["transmitter"]]
            elif regexSignalInfo is not None:
                if inMessage is not None:
                    thisSignalInfo = GetSignalInfo(regexSignalInfo, inMessage[0], inMessage[1])
                    signalName = thisSignalInfo["name"]
                    if thisSignalInfo["endianness"] == "big":
                        raise Exception(f"Unsupported big endian signal on line {idx+1}: {signalName}")
                    if thisSignalInfo["isMuxer"]:
                        # Update message info to include the muxer signal
                        messageInfo[-1]["muxer"] = signalName
                    if thisSignalInfo["muxIdx"] is not None:
                        # Update message info to reflect the number of muxes
                        messageInfo[-1]["maxMuxIdx"] = max(
                            messageInfo[-1]["maxMuxIdx"],
                            thisSignalInfo["muxIdx"]
                        )
                    signalInfo += [thisSignalInfo]
                    signalNames += [signalName]
                else:
                    raise Exception(f"Signal info found without a message on line {idx+1}: {signalName}")
            else:
                inMessage = None

            if regexSignalValTableInfo is not None:
                thisSignalInfo = GetSignalValTableInfo(regexSignalValTableInfo)
                signalName = thisSignalInfo["signal"]
                if signalName not in signalNames:
                    raise Exception(f"Value table listed for unidentified signal {signalName}")
                if thisSignalInfo["description"].lower() == "sna":
                    # Only support SNA value table entry
                    signalIdx = signalNames.index(signalName)
                    signalInfo[signalIdx]["SNA"] = thisSignalInfo["value"]
                    # Replace convType with QualifiedVal type
                    convType = signalInfo[signalIdx]["convType"]
                    signalInfo[signalIdx]["convType"] = RemoveSuffix(convType, "_t") + "_q"

            if regexMessageCycleTimeInfo is not None:
                thisMessageInfo = GetMessageCycleTimeInfo(regexMessageCycleTimeInfo)
                messageId = thisMessageInfo["id"]
                if messageId not in messageIds:
                    raise Exception(f"Cycle time listed for unidentified message ID {messageId}")
                if thisMessageInfo["cycleTime"] > 0:
                    # Only support non-zero entries
                    messageIdx = messageIds.index(messageId)
                    # Update message cycleTime
                    messageInfo[messageIdx]["cycleTime"] = thisMessageInfo["cycleTime"]


        if self.genDebugFiles:
            for signal in signalInfo:
                self.signalInfoFileHandle.write(str(signal) + "\n")
            for message in messageInfo:
                self.messageInfoFileHandle.write(str(message) + "\n")


        # Check for errors
        # - duplicate message IDs
        # - multiplexed message with no muxer
        # - message with more than one muxer
        # - multiplexed signal with mux index out of range
        # - message with signal extending beyond message length
        # - message with zero or negative cycle time
        messageIds = []
        for message in messageInfo:
            messageName = message["name"]
            messageId = message["id"]
            if messageId in messageIds:
                raise Exception(f"Duplicate message ID {messageId} found for message {messageName}")
            messageIds += [messageId]
            if message["muxer"] is None and message["maxMuxIdx"] > -1:
                raise Exception(f"Message identified with muxed frames and no muxer: {messageName}")
            thisMessageSignalInfo = [s for s in signalInfo if s["message"] == messageName]
            messageMuxer = None
            maxEndBitId = 0
            for signal in thisMessageSignalInfo:
                signalName = signal["name"]
                if signal["isMuxer"]:
                    if messageMuxer is not None:
                        raise Exception(f"Message identified with more than one muxer: {messageName} with muxers {messageMuxer} and {signalName}")
                    else:
                        messageMuxer = signalName
                if signal["muxIdx"] is not None and signal["muxIdx"] > message["maxMuxIdx"]:
                    raise Exception(f"Mux index out of range: {messageName} signal {signalName}")
                maxEndBitId = max(maxEndBitId, signal["startBit"] + signal["bitLength"])
            if (maxEndBitId > (message["length"] * 8)):
                raise Exception(f"Message with shorter length than required for signals: {messageName} with DLC {message['length']} and max bit idx {str(maxEndBitId-1)}")
            if (message["cycleTime"] <= 0):
                raise Exception(f"Message with zero or negative cycle time: {messageName} with cycle time {message['cycleTime']}")


        # Check for errors
        # - signal min value out of range
        # - signal max value out of range
        # - signal SNA value out of range
        for signal in signalInfo:
            signed = signal["signed"]
            bitLength = signal["bitLength"]
            minValue = signal["min"]
            maxValue = signal["max"]
            snaValue = signal.get("SNA", None)
            # Min and max values are represented with scale and offset applied
            # Signed min is -2^(bitLength-1)
            # Signed max is  2^(bitLength-1) - 1
            minValid = -(2 ** (bitLength-1))     if signed else 0
            maxValid =  (2 ** (bitLength-1)) - 1 if signed else (2 ** bitLength) - 1
            minValid = (minValid * signal["scale"]) + signal["offset"]
            maxValid = (maxValid * signal["scale"]) + signal["offset"]
            if minValue < minValid:
                raise Exception(f"Min value for signal {signal['name']} with value {minValue} violates min valid value of {minValid}")
            if maxValue > maxValid:
                raise Exception(f"Max value for signal {signal['name']} with value {maxValue} violates max valid value of {maxValid}")
            if snaValue is not None:
                # SNA value is represented as an unsigned int here with no conversion
                # Signed min as unsigned is 2^(bitLength-1)
                # Signed max as unsigned is 2^(bitLength-1) - 1
                minValid = 0
                maxValid = (2 ** (bitLength-1)) if signed else (2 ** bitLength) - 1
                if snaValue < minValid or snaValue > maxValid:
                    raise Exception(f"SNA value for signal {signal['name']} with value {snaValue} violates signal width of {bitLength}")


        # Filter for transmit info
        signalsToTransmit = [s for s in signalInfo if s["transmitter"] == self.node]
        messagesToTransmit = [m for m in messageInfo if m["transmitter"] == self.node]
        # Get the relevant (message, muxIdx) pairs based on the signals to transmit
        messageMuxPairsToTransmit = list(set([(s["message"], s["muxIdx"]) for s in signalsToTransmit]))
        messageMuxesToTransmit = {}
        for (messageName, messageMuxIdx) in messageMuxPairsToTransmit:
            if messageName in messageMuxesToTransmit:
                messageMuxesToTransmit[messageName] += [messageMuxIdx]
            else:
                messageMuxesToTransmit[messageName] = [messageMuxIdx]
        # Amend transmit message info with the specific muxes that contain relevant signals
        for idx, message in enumerate(messagesToTransmit):
            transmitMuxIdxs = messageMuxesToTransmit[message["name"]]
            transmitMuxIdxs.remove(None)
            transmitMuxIdxs.sort()
            messagesToTransmit[idx]["transmitMuxIdxs"] = transmitMuxIdxs


        # Filter for receive info
        signalsToReceive = [s for s in signalInfo if any([re.search(expr, s["name"]) for expr in self.rxExpressions])]
        signalsToReceive = [s for s in signalsToReceive if s["transmitter"] != self.node]
        # Replace convType with QualifiedVal type
        for idx, signal in enumerate(signalsToReceive):
            convType = signalsToReceive[idx]["convType"]
            if not convType.endswith("_q"):
                signalsToReceive[idx]["convType"] = RemoveSuffix(convType, "_t") + "_q"
        # Get the relevant (message, muxIdx) pairs based on the signals to receive
        messageMuxPairsToReceive = list(set([(s["message"], s["muxIdx"]) for s in signalsToReceive]))
        messageMuxesToReceive = {}
        for (messageName, messageMuxIdx) in messageMuxPairsToReceive:
            if messageName in messageMuxesToReceive:
                messageMuxesToReceive[messageName] += [messageMuxIdx]
            else:
                messageMuxesToReceive[messageName] = [messageMuxIdx]
        messagesToReceive = [m for m in messageInfo if m["name"] in messageMuxesToReceive]
        # Amend recieve message info with the specific muxes that contain relevant signals
        for idx, message in enumerate(messagesToReceive):
            receiveMuxIdxs = messageMuxesToReceive[message["name"]]
            receiveMuxIdxs.remove(None)
            receiveMuxIdxs.sort()
            messagesToReceive[idx]["receiveMuxIdxs"] = receiveMuxIdxs


        configDict = {
            "alias": self.alias,
            "messagesToTransmit": sorted(messagesToTransmit, key=lambda d: d["name"]),
            "signalsToTransmit": sorted(signalsToTransmit, key=lambda d: d["name"]),
            "messagesToReceive": sorted(messagesToReceive, key=lambda d: d["name"]),
            "signalsToReceive": sorted(signalsToReceive, key=lambda d: d["name"]),
        }
        Render(targetDir=self.generatedCodeDirPath, alias=self.alias, configDict=configDict)

        self.Finish()


#---------------------------------------------------------------------------------------------------
# Parse and run
#---------------------------------------------------------------------------------------------------
def get_args():

    def key_arg(key):
        try:
            return eval("dict(%s)" % key)
        except:
            raise argparse.ArgumentError("%s is not a valid key" % key)

    parser = argparse.ArgumentParser()
    parser.add_argument("--dbcFile", dest="dbcFile", help="Input DBC file")
    parser.add_argument("--rxFile", dest="rxFile", help="Generated code target directory", default=None)
    parser.add_argument("--targetDir", dest="targetDir", help="Generated code target directory")
    parser.add_argument("--alias", dest="alias", help="Alias/namespace for code generation")
    parser.add_argument("--node", dest="node", help="Transmit node name")
    parser.add_argument("--genDebugFiles", dest="genDebugFiles", action="store_true", default=False)

    return parser.parse_args()


if __name__ == "__main__":
    args = get_args()
    print(f"Generating CAN code for alias: {args.alias}, node: {args.node}")
    sampleCodeGen = DbcCodeGen(args.dbcFile, args.rxFile, args.targetDir, args.alias, args.node, args.genDebugFiles)
    sampleCodeGen.Run()
