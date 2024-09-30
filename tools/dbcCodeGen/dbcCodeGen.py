import os, re

#---------------------------------------------------------------------------------------------------
# Constants
#---------------------------------------------------------------------------------------------------
BIT_LENGTH_FROM_TYPE = {"int8_t": 8, "int16_t": 16, "int32_t": 32, "int64_t": 64}

#---------------------------------------------------------------------------------------------------
# Helper functions - data type interpretation
#---------------------------------------------------------------------------------------------------
def GetNumberFromString(number):
    try:
        return int(number)
    except:
        return float(number)


def GetIntTypeFromBitLength(bitLength, signed):
    typeStr = "" if signed else "u"
    if bitLength <= 8:
        return typeStr + "int8_t"
    elif bitLength <= 16:
        return typeStr + "int16_t"
    elif bitLength <= 32:
        return typeStr + "int32_t"
    elif bitLength <= 64:
        return typeStr + "int64_t"
    else:
        return ""  # Error - too long


def GetRawTypeFromBitLength(bitLength):
    return GetIntTypeFromBitLength(bitLength, False)


def GetTypeFromSignAndConv(bitLength, signed, scale, offset):
    isInteger = (type(scale) is int) and (type(offset) is int)
    if isInteger:
        convIntType = GetIntTypeFromBitLength(bitLength, signed)
        if signed:
            return "int64_t" if (convIntType == "int64_t") else "int32_t"
        else:
            return "uint64_t" if (convIntType == "uint64_t") else "uint32_t"
    else:
        return "float"


#---------------------------------------------------------------------------------------------------
# Helper functions - parsing
#---------------------------------------------------------------------------------------------------
RE_SEARCH_MESSAGE_START = "(?<=^BO_) (\d+) (\S+): (\d+) (\S+)"
def GetMessageInfo(regexMessageStart):
    messageName = regexMessageStart.group(2)
    messageId = regexMessageStart.group(1)
    messageLength = regexMessageStart.group(3)
    messageTransmitter = regexMessageStart.group(4)
    return {
        "name": messageName,
        "id": int(messageId),
        "length": int(messageLength),
        "transmitter": messageTransmitter,
        "muxer": None,
        "maxMuxIdx": -1
    }


RE_SEARCH_SIGNAL_INFO = "(?<=^ SG_) (\S+) ((\S+) )*: (\d+)\|(\d+)@([01])([+-]) \(([-\d\.e]+),([-\d\.e]+)\) \[([-\d\.e]+)\|([-\d\.e]+)\]"
def GetSignalInfo(regexSignalInfo, messageName, transmitter):
    signalName = regexSignalInfo.group(1)
    signalMux = regexSignalInfo.group(3)
    signalStartBit = regexSignalInfo.group(4)
    signalBitLength = regexSignalInfo.group(5)
    signalEndianness = regexSignalInfo.group(6)
    signalSignedness = regexSignalInfo.group(7)
    signalScale = regexSignalInfo.group(8)
    signalOffset = regexSignalInfo.group(9)
    signalMin = regexSignalInfo.group(10)
    signalMax = regexSignalInfo.group(11)
    isMuxer = signalMux == "M"
    muxedSignal = signalMux is not None and not isMuxer
    bitLength = int(signalBitLength)
    signed = False if (signalSignedness == "+") else True
    scale = GetNumberFromString(signalScale)
    offset = GetNumberFromString(signalOffset)
    anyFloat = any([type(v) is float for v in [scale, offset]])
    return {
        "name": signalName,
        "message": messageName,
        "transmitter": transmitter,
        "isMuxer": isMuxer,
        "muxIdx": int(signalMux[1:]) if muxedSignal else None,
        "startBit": int(signalStartBit),
        "bitLength": bitLength,
        "endianness": "little" if (signalEndianness == "1") else "big",
        "signed": signed,
        "scale": float(scale) if anyFloat else scale,
        "offset": float(offset) if anyFloat else offset,
        "min": GetNumberFromString(signalMin),
        "max": GetNumberFromString(signalMax),
        "rawType": GetRawTypeFromBitLength(bitLength),
        "convIntType": GetIntTypeFromBitLength(bitLength, signed),
        "convType": GetTypeFromSignAndConv(bitLength, signed, scale, offset)
    }


#---------------------------------------------------------------------------------------------------
# Helper functions - code gen
#---------------------------------------------------------------------------------------------------
def PrintHeaderFileStart(fileHandle, guard):
    fileHandle.write("#ifndef " + guard + "\n" + "#define " + guard + "\n\n")
    fileHandle.write("#ifdef __cplusplus\n" + "extern \"C\" {\n" + "#endif\n\n")


def PrintHeaderFileEnd(fileHandle, guard):
    fileHandle.write("#ifdef __cplusplus\n" + "}\n" + "#endif\n\n")
    fileHandle.write("#endif // " + guard + "\n")


def PrintSubSectionHeader(fileHandle, header):
    fileHandle.write("//--------------------------------------------------------------------------------------------------\n")
    fileHandle.write("// " + header + "\n")
    fileHandle.write("//--------------------------------------------------------------------------------------------------\n")


def PrintInclude(fileHandle, name):
    fileHandle.write("#include \"" + name + "\"\n")


def PrintDefine(fileHandle, name, value, signed=False):
    valueSigned = value + ("" if signed else "U")
    fileHandle.write("#define " + name + " (" + valueSigned + ")\n")


def GetByteMaskAndShift(byte, mask, shift, shiftLeft=True):
    strToWrite = "(" + byte + ")"
    if mask != 0xFF:
        strToWrite = "(" + strToWrite + " & " +"0x{:02X}".format(mask) + ")"
    if shift > 0:
        shiftDir = " << " if shiftLeft else " >> "
        strToWrite = "(" + strToWrite + shiftDir + str(shift) + ")"
    return strToWrite


def GetMsgProcessName(messageName):
    return "ProcessM_" + messageName
def GetSignalGetRawFromFrameName(signalName):
    return "GetSRawFromFrame_" + signalName
def GetSignalGetRawName(signalName):
    return "GetSRaw_" + signalName
def GetSignalGetFromFrameName(signalName):
    return "GetSFromFrame_" + signalName
def GetSignalGetName(signalName):
    return "GetS_" + signalName
def GetMsgMidName(messageName):
    return messageName + "_MID"
def GetMsgDlcName(messageName):
    return messageName + "_DLC"
def GetRxArrVarName(messageName):
    return "g" + messageName + "_RX_ARR"
def GetRxArrLenName(messageName):
    return messageName + "_RX_ARR_LEN"
def GetRxArrIdxName(messageName, muxIdx):
    return "0U" if muxIdx == "None" else messageName + "_M" + muxIdx + "_RX_ARR_IDX"
def GetLatestRxArrPtrName(messageName):
    return "g" + messageName + "_LatestRxPtr"


def FLWI(line, indent=0):  # FormatLineWithIndent
    indentStr = "    " * indent
    line = indentStr + line.replace("\n", "\n" + indentStr).rstrip(" ")
    line = line.replace("\n" + indentStr + "\n", "\n\n").rstrip(" ")
    return line


#---------------------------------------------------------------------------------------------------
# Code gen
#---------------------------------------------------------------------------------------------------
def PrintMessageInfo(fileHandle, transmitMessageInfo, receiveMessageInfo):
    def PrintRequiredMessageInfo(message):
        messageName = message["name"]
        fileHandle.write("// " + messageName + "\n")
        PrintDefine(fileHandle, GetMsgMidName(messageName), str(message["id"]))
        PrintDefine(fileHandle, GetMsgDlcName(messageName), str(message["length"]))

    PrintHeaderFileStart(fileHandle, "MESSAGE_INFO_H")
    PrintSubSectionHeader(fileHandle, "Transmit message info macros")
    for message in transmitMessageInfo:
        PrintRequiredMessageInfo(message)
        fileHandle.write("\n")

    PrintSubSectionHeader(fileHandle, "Receive message info macros")
    for message in receiveMessageInfo:
        PrintRequiredMessageInfo(message)
        messageName = message["name"]
        receiveMuxIdxs = message["receiveMuxIdxs"]
        for idx, muxIdx in enumerate(receiveMuxIdxs):
            PrintDefine(fileHandle, GetRxArrIdxName(messageName, str(muxIdx)), str(idx))
        PrintDefine(fileHandle, GetRxArrLenName(messageName), str(max(1, len(receiveMuxIdxs))))
        fileHandle.write("\n")
    PrintHeaderFileEnd(fileHandle, "MESSAGE_INFO_H")


def PrintGetters(fileHandle, signalInfo):
    pass


def PrintReceiver(fileHandle, messageInfo, signalInfo):
    """
    Signal-level functions
    """
    def PrintSignalConvertedUnpacker(signal, indent=1):
        signalName = signal["name"]
        bitLength = signal["bitLength"]
        signed = signal["signed"]
        convIntType = signal["convIntType"]
        convType = signal["convType"]
        getRawFromFrameName = GetSignalGetRawFromFrameName(signalName)
        strToWrite = ""
        strToWrite += convIntType + " raw = (" + convIntType + ")" + getRawFromFrameName + "(pData);\n"
        if signed:
            # Signed integer - use sign-extended raw
            bitsToShift = BIT_LENGTH_FROM_TYPE[convIntType] - bitLength
            if bitsToShift > 0:
                strToWrite += "// Sign extend\n"
                strToWrite += "raw = (raw << " + str(bitsToShift) + ") >> " + str(bitsToShift) + ";\n"
        convAppend = "F" if convType == "float" else "U" if convType.startswith("u") else ""
        scale = str(signal["scale"]) + convAppend
        offset = str(signal["offset"]) + convAppend
        strToWrite += convType + " converted = (((" + convType + ")raw) * " + scale + ") + " + offset + ";\n"
        strToWrite += "return converted;\n"
        fileHandle.write(FLWI(strToWrite, indent))

    def PrintSignalRawUnpacker(signal, indent=1):
        startBit = signal["startBit"]
        bitLength = signal["bitLength"]
        rawType = signal["rawType"]
        endBit = startBit + bitLength - 1
        startByte = int(startBit / 8)
        endByte = int(endBit / 8)
        startRShift = startBit % 8
        startLShift = 8 - startRShift
        startByteMask = (0xFF << startRShift) & 0xFF
        endByteMask = (0xFF >> (7 - (endBit % 8)))
        strToWrite = "const " + rawType + " rawVal = "
        if startByte == endByte:
            overallByteMask = startByteMask & endByteMask
            strToWrite += GetByteMaskAndShift("pData[" + str(startByte) + "]", overallByteMask, startRShift, False) + ";\n"
        else:
            strToWrite += GetByteMaskAndShift("pData[" + str(startByte) + "]", startByteMask, startRShift, False)
            lshift = startLShift
            for byte in range(startByte+1, endByte):
                strToWrite += " + " + GetByteMaskAndShift("pData[" + str(byte) + "]", 0xFF, lshift)
                lshift += 8
            strToWrite += " + " + GetByteMaskAndShift("pData[" + str(endByte) + "]", endByteMask, lshift) + ";\n"
        strToWrite += "return rawVal;\n"
        fileHandle.write(FLWI(strToWrite, indent))

    def PrintSignalReceiver(signal):
        signalName = signal["name"]
        messageName = signal["message"]
        signalMuxIdx = signal["muxIdx"]
        rawType = signal["rawType"]
        convType = signal["convType"]
        thisSignalMessageInfo = [m for m in messageInfo if m["name"] == messageName][0]
        messageIsMuxed = thisSignalMessageInfo["muxer"] is not None
        # Unpack raw with a frame arg
        getRawFromFrameName = GetSignalGetRawFromFrameName(signalName)
        fileHandle.write("static " + rawType + " " + getRawFromFrameName + "(const uint8_t * const pData)\n{\n")
        PrintSignalRawUnpacker(signal)
        fileHandle.write("}\n")
        # Unpack raw without a frame arg - requires a frame pointer
        getRawName = GetSignalGetRawName(signalName)
        strToWrite = ""
        strToWrite += "static " + rawType + " " + getRawName + "(void)\n{\n"
        strDataPtr = ""  # Save this, can be used below
        if signalMuxIdx is None and messageIsMuxed:
            latestRxArrPtrName = GetLatestRxArrPtrName(messageName)
            strDataPtr += FLWI("// This signal belongs to a muxed message but is static. Get contents from latest-received frame\n", 1)
            strDataPtr += FLWI("const uint8_t * const pData = " + latestRxArrPtrName + ";\n", 1)
        else:
            rxArrVarName = GetRxArrVarName(messageName)
            rxArrIdxName = GetRxArrIdxName(messageName, str(signalMuxIdx))
            strDataPtr += FLWI("const uint8_t * const pData = &" + rxArrVarName + "[" + rxArrIdxName + "][0U];\n", 1)
        strToWrite += strDataPtr + FLWI("return " + getRawFromFrameName + "(pData);\n", 1) + "}\n"
        fileHandle.write(strToWrite)
        # Unpack converted with a frame arg
        getFromFrameName = GetSignalGetFromFrameName(signalName)
        fileHandle.write("static " + convType + " " + getFromFrameName + "(const uint8_t * const pData)\n{\n")
        PrintSignalConvertedUnpacker(signal)
        fileHandle.write("}\n")
        # Unpack converted without a frame arg - requires a frame pointer
        getName = GetSignalGetName(signalName)
        strToWrite = ""
        strToWrite += "static " + convType + " " + getName + "(void)\n{\n"
        strToWrite += strDataPtr + FLWI("return " + getFromFrameName + "(pData);\n", 1) + "}\n\n"
        fileHandle.write(strToWrite)

    """
    Message-level functions
    """
    def PrintMessageMuxReceiver(thisMuxSignalInfo, indent=1):
        messageName = thisMuxSignalInfo[0]["message"]
        latestRxArrPtrName = GetLatestRxArrPtrName(messageName)
        rxArrVarName = GetRxArrVarName(messageName)
        rxArrIdxName = GetRxArrIdxName(messageName, str(thisMuxSignalInfo[0]["muxIdx"]))
        strToWrite = ""
        strToWrite += FLWI(latestRxArrPtrName + " = &" + rxArrVarName + "[" + rxArrIdxName + "][0U];\n", indent)
        fileHandle.write(strToWrite)

    def PrintMessageReceiver(message):
        messageName = message["name"]
        muxer = message["muxer"]
        thisMessageSignalInfo = [s for s in signalInfo if s["message"] == messageName]

        # Private function
        fileHandle.write("static bool " + GetMsgProcessName(messageName) + "(const uint8_t * const pData)\n{\n")
        fileHandle.write(FLWI("bool success = true;\n", 1))

        if muxer is not None:
            getRawFromFrameName = GetSignalGetRawFromFrameName(muxer)
            fileHandle.write(FLWI("const uint32_t muxIdx = " + getRawFromFrameName + "(pData);\n\n", 1))
            # Get the unique muxes for this message
            uniqueMuxes = list(set([s["muxIdx"] for s in thisMessageSignalInfo if s["muxIdx"] is not None]))
            # Switch on mux
            fileHandle.write(FLWI("switch (muxIdx)\n{\n", 1))
            for mux in uniqueMuxes:
                # Get the signals for this mux
                thisMuxSignalInfo = [s for s in thisMessageSignalInfo if s["muxIdx"] == mux]
                fileHandle.write(FLWI("case " + str(mux) + "U:\n{\n", 2))
                PrintMessageMuxReceiver(thisMuxSignalInfo, 3)
                fileHandle.write(FLWI("break;\n", 3) + FLWI("}\n", 2))
            strToWrite = ""
            strToWrite += FLWI("default:\n{\n", 2) + FLWI("success = false;\nbreak;\n", 3) + FLWI("}\n", 2)
            strToWrite += FLWI("}\n\n", 1)
            fileHandle.write(strToWrite)
        else:
            fileHandle.write("\n")
            PrintMessageMuxReceiver(thisMessageSignalInfo)
            fileHandle.write("\n")

        messageDlc = GetMsgDlcName(messageName)
        latestRxArrPtrName = GetLatestRxArrPtrName(messageName)
        strToWrite = ""
        strToWrite += FLWI("if (success)\n", 1)
        strToWrite += FLWI("{\n", 1)
        strToWrite += FLWI("for (uint32_t d = 0U; d < " + messageDlc + "; ++d)\n{\n", 2)
        strToWrite += FLWI(latestRxArrPtrName + "[d] = pData[d];\n", 3)
        strToWrite += FLWI("}\n", 2) + FLWI("}\n\n", 1)
        fileHandle.write(strToWrite)

        # Return
        fileHandle.write(FLWI("return success;\n", 1) + "}\n\n")

    """
    Main file generation
    """
    # Includes
    PrintInclude(fileHandle, "messageInfo.h")
    PrintInclude(fileHandle, "stdbool.h")
    PrintInclude(fileHandle, "stdint.h")
    fileHandle.write("\n")

    # Storage private vars
    PrintSubSectionHeader(fileHandle, "Receive message storage")
    for message in messageInfo:
        messageName = message["name"]
        rxArrVarName = GetRxArrVarName(messageName)
        messageRxArrLen = GetRxArrLenName(messageName)
        messageDlc = GetMsgDlcName(messageName)
        fileHandle.write("static uint8_t " + rxArrVarName + "[" + messageRxArrLen + "][" + messageDlc + "];\n")
        latestRxArrPtrName = GetLatestRxArrPtrName(messageName)
        fileHandle.write("static uint8_t * " + latestRxArrPtrName + " = &" + rxArrVarName + "[0U][0U];\n")
    fileHandle.write("\n")

    # Unpack signal private functions
    PrintSubSectionHeader(fileHandle, "Signal receive unpack functions")
    for signal in signalInfo:
        fileHandle.write("// " + signal["name"] + "\n")
        PrintSignalReceiver(signal)

    # Unpack message private functions
    PrintSubSectionHeader(fileHandle, "Message receive storage functions")
    for message in messageInfo:
        PrintMessageReceiver(message)

    # Public function
    PrintSubSectionHeader(fileHandle, "Message receive hook")
    fileHandle.write("bool CanReceive(const uint8_t mid, const uint8_t dlc, const uint8_t * const pData)\n{\n")
    fileHandle.write(FLWI("bool success = true;\n\n", 1))
    # Switch on message ID
    fileHandle.write(FLWI("switch (mid)\n{\n", 1))
    for message in messageInfo:
        messageName = message["name"]
        strToWrite = ""
        strToWrite += FLWI("case " + GetMsgMidName(messageName) + ":\n{\n", 2)
        strToWrite += FLWI("if (dlc != " + GetMsgDlcName(messageName) + ")\n{\n", 3) + FLWI("success = false;\n", 4) + FLWI("}\n", 3)
        strToWrite += FLWI("else\n{\n", 3) + FLWI("success = " + GetMsgProcessName(messageName) + "(pData);\n", 4) + FLWI("}\nbreak;\n", 3)
        strToWrite += FLWI("}\n", 2)
        fileHandle.write(strToWrite)
    strToWrite = ""
    strToWrite += FLWI("default:\n{\n", 2) + FLWI("success = false;\nbreak;\n", 3) + FLWI("}\n", 2)
    strToWrite += FLWI("}\n\n", 1)
    fileHandle.write(strToWrite)

    # Return
    fileHandle.write(FLWI("return success;\n", 1) + "}\n")


#---------------------------------------------------------------------------------------------------
# Code
#---------------------------------------------------------------------------------------------------
dbcFile = "Sample.dbc"
signalInfoFile = "generated/signals.txt"
messageInfoFile = "generated/messages.txt"
messageConstantsFile = "generated/messageInfo.h"
canReceiverFile = "generated/canReceiver.c"

dbcFileHandle = open(dbcFile, "r")


# Parse DBC file for message and signal info
inMessage = None
messageInfo = []
signalInfo = []
for idx, line in enumerate(dbcFileHandle):
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


# TODO Create RAM storage for each mux of each transmit message
# Setters/getters touch the corresponding mux of the corresponding message
# Transmitter logic should then access the message/mux storage to transmit based on the TX schedule

if not os.path.exists(os.path.dirname(signalInfoFile)):
    os.mkdir(os.path.dirname(signalInfoFile))
signalInfoFileHandle = open(signalInfoFile, "w")
messageInfoFileHandle = open(messageInfoFile, "w")
messageConstantsFileHandle = open(messageConstantsFile, "w")
canReceiverFileHandle = open(canReceiverFile, "w")


# Filter for transmit info
signalsToTransmit = [s for s in signalInfo if s["transmitter"] == "SAMPLE_A"]  # TODO filter this properly
messagesToTransmit = [m for m in messageInfo if m["transmitter"] == "SAMPLE_A"]  # TODO filter this properly
signalsToTransmit = signalInfo  # TODO Remove
messagesToTransmit = messageInfo  # TODO Remove


# Filter for receive info
signalsToReceive = [s for s in signalInfo if s["transmitter"] == "SAMPLE_B"]  # TODO filter this properly
signalsToReceive = signalInfo  # TODO Remove
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


for signal in signalInfo:
    signalInfoFileHandle.write(str(signal) + "\n")

for message in messageInfo:
    messageInfoFileHandle.write(str(message) + "\n")


# TODO Should filter these messages from the DBC as those this particular node transmits/receives
PrintMessageInfo(messageConstantsFileHandle, messagesToTransmit, messagesToReceive)

# TODO Should filter these signals from the DBC as those this particular node receives,
# can then filter the messages based on those that appear in the filtered signals
PrintReceiver(canReceiverFileHandle, messagesToReceive, signalsToReceive)

dbcFileHandle.close()
signalInfoFileHandle.close()
messageInfoFileHandle.close()
messageConstantsFileHandle.close()
canReceiverFileHandle.close()
