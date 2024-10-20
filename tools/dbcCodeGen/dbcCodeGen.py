import argparse, os, re
from helpers import *

#---------------------------------------------------------------------------------------------------
# Class for code generation management
#---------------------------------------------------------------------------------------------------
class DbcCodeGen:
    from _genInfo import PrintMessageInfo
    from _genReceiver import PrintReceiverHeader, PrintReceiver
    from _genTransmitter import PrintTransmitterHeader, PrintTransmitter
    from helpers import (
        GetMsgTransmitMuxIdxGetName,
        GetMsgTransmitStorageGetName,
        GetTxArrLenName,
        GetTxArrIdxName,
        GetSignalSetRawFromFrameName,
        GetSignalSetRawName,
        GetSignalSetFromFrameName,
        GetSignalSetName,
        GetRxNumMsg,
        GetMsgReceiveMidIdxGetName,
        GetRxArrLenName,
        GetRxArrIdxName,
        GetSignalGetRawFromFrameName,
        GetSignalGetRawName,
        GetSignalGetFromFrameName,
        GetSignalGetName,
        GetMsgMidName,
        GetMsgDlcName,
        GetMsgMaxMuxName
    )


    def __init__(self, dbcFilePath, generatedCodeDirPath, alias, node, genDebugFiles):
        self.alias = alias
        self.node = node
        self.genDebugFiles = genDebugFiles

        self.dbcFileHandle = open(dbcFilePath, "r")
        if not os.path.exists(generatedCodeDirPath):
            os.mkdir(generatedCodeDirPath)

        messageConstantsFile = os.path.join(generatedCodeDirPath, f"{alias}_messageInfo.h")
        canReceiverHeaderFile = os.path.join(generatedCodeDirPath, f"{alias}_canReceiver.h")
        canReceiverFile = os.path.join(generatedCodeDirPath, f"{alias}_canReceiver.c")
        canTransmitterHeaderFile = os.path.join(generatedCodeDirPath, f"{alias}_canTransmitter.h")
        canTrasmitterFile = os.path.join(generatedCodeDirPath, f"{alias}_canTransmitter.c")

        self.messageConstantsFileHandle = open(messageConstantsFile, "w")
        self.canReceiverHeaderFileHandle = open(canReceiverHeaderFile, "w")
        self.canReceiverFileHandle = open(canReceiverFile, "w")
        self.canTransmitterHeaderFileHandle = open(canTransmitterHeaderFile, "w")
        self.canTransmitterFileHandle = open(canTrasmitterFile, "w")

        if genDebugFiles:
            signalInfoFile = os.path.join(generatedCodeDirPath, f"{alias}_signals.txt")
            messageInfoFile = os.path.join(generatedCodeDirPath, f"{alias}_messages.txt")
            self.signalInfoFileHandle = open(signalInfoFile, "w")
            self.messageInfoFileHandle = open(messageInfoFile, "w")


    def Finish(self):
        self.dbcFileHandle.close()
        self.messageConstantsFileHandle.close()
        self.canReceiverHeaderFileHandle.close()
        self.canReceiverFileHandle.close()
        self.canTransmitterHeaderFileHandle.close()
        self.canTransmitterFileHandle.close()

        if self.genDebugFiles:
            self.signalInfoFileHandle.close()
            self.messageInfoFileHandle.close()


    def Run(self):
        # Parse DBC file for message and signal info
        inMessage = None
        messageInfo = []
        signalInfo = []
        for idx, line in enumerate(self.dbcFileHandle):
            regexMessageStart = re.search(RE_SEARCH_MESSAGE_START, line)
            regexSignalInfo = re.search(RE_SEARCH_SIGNAL_INFO, line)

            if regexMessageStart is not None:
                thisMessageInfo = GetMessageInfo(regexMessageStart)
                messageInfo += [thisMessageInfo]
                inMessage = [thisMessageInfo["name"], thisMessageInfo["transmitter"]]
            elif regexSignalInfo is not None:
                thisSignalInfo = GetSignalInfo(regexSignalInfo, inMessage[0], inMessage[1])
                signalName = thisSignalInfo["name"]
                if inMessage is not None:
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
                else:
                    raise Exception(f"Signal info found without a message on line {idx+1}: {signalName}")
            else:
                inMessage = None


        # Check for errors
        for message in messageInfo:
            messageName = message["name"]
            if message["muxer"] is None and message["maxMuxIdx"] > -1:
                raise Exception(f"Message identified with muxed frames and no muxer: {messageName}")
            thisMessageSignalInfo = [s for s in signalInfo if s["message"] == messageName]
            messageMuxer = None
            maxEndBitId = 0
            for signal in thisMessageSignalInfo:
                signalName = signal["name"]
                if signal["isMuxer"] and messageMuxer is not None:
                    raise Exception(f"Message identified with more than one muxer: {messageName} with muxers {messageMuxer} and {signalName}")
                else:
                    messageMuxer = signalName
                if signal["muxIdx"] is not None and signal["muxIdx"] > message["maxMuxIdx"]:
                    raise Exception(f"Mux index out of range: {messageName} signal {signalName}")
                maxEndBitId = max(maxEndBitId, signal["startBit"] + signal["bitLength"])
            if (maxEndBitId > (message["length"] * 8)):
                raise Exception(f"Message with shorter length than required for signals: {messageName} with DLC {message['length']} and max bit idx {str(maxEndBitId-1)}")


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
        # TODO This could be filtered better, just do anything that isn't the transmit node
        signalsToReceive = [s for s in signalInfo if s["transmitter"] != self.node]
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


        if self.genDebugFiles:
            for signal in signalInfo:
                self.signalInfoFileHandle.write(str(signal) + "\n")
            for message in messageInfo:
                self.messageInfoFileHandle.write(str(message) + "\n")


        self.PrintMessageInfo(messagesToTransmit, messagesToReceive)

        self.PrintReceiverHeader(signalsToReceive)
        self.PrintReceiver(messagesToReceive, signalsToReceive)

        self.PrintTransmitterHeader(messagesToTransmit, signalsToTransmit)
        self.PrintTransmitter(messagesToTransmit, signalsToTransmit)

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
    parser.add_argument("--targetDir", dest="targetDir", help="Generated code target directory")
    parser.add_argument("--alias", dest="alias", help="Alias/namespact for code generation")
    parser.add_argument("--node", dest="node", help="Transmit node name")
    parser.add_argument("--genDebugFiles", dest="genDebugFiles", action="store_true", default=False)

    return parser.parse_args()


if __name__ == "__main__":
    args = get_args()
    sampleCodeGen = DbcCodeGen(args.dbcFile, args.targetDir, args.alias, args.node, args.genDebugFiles)
    sampleCodeGen.Run()