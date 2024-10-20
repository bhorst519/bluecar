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
    min = GetNumberFromString(signalMin)
    max = GetNumberFromString(signalMax)
    anyFloat = any([type(v) is float for v in [scale, offset, min, max]])
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
        "min": float(min) if anyFloat else min,
        "max": float(max) if anyFloat else max,
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
    fileHandle.write( "//--------------------------------------------------------------------------------------------------\n")
    fileHandle.write(f"// {header}\n")
    fileHandle.write( "//--------------------------------------------------------------------------------------------------\n")


def PrintInclude(fileHandle, name):
    fileHandle.write(f"#include \"{name}\"\n")


def PrintDefine(fileHandle, name, value, signed=False):
    valueSigned = value + ("" if signed else "U")
    fileHandle.write(f"#define {name} ({valueSigned})\n")


def GetByteMaskAndShift(byte, mask, shift, shiftLeft=True):
    strToWrite = f"({byte})"
    if mask != 0xFF:
        maskHex = "0x{:02X}".format(mask)
        strToWrite = f"({strToWrite} & {maskHex})"
    if shift > 0:
        shiftDir = " << " if shiftLeft else " >> "
        strToWrite = f"({strToWrite}{shiftDir}{shift})"
    return strToWrite


def GetShiftAndByteMask(byte, shift, mask, shiftLeft=True):
    strToWrite = f"({byte})"
    if shift > 0:
        shiftDir = " << " if shiftLeft else " >> "
        strToWrite = f"({strToWrite}{shiftDir}{shift})"
    maskHex = "0x{:02X}".format(mask)
    strToWrite = f"({strToWrite} & {maskHex})"
    return strToWrite


# Transmit - mux index helper getters
def GetMsgTransmitMuxIdxGetName(self, messageName):
    return f"CANTX_{self.alias}_GetMuxFromIdx_{messageName}"
def GetMsgTransmitMuxIdxVarName(messageName):
    return f"g{messageName}_MuxFromIdx"


# Transmit - storage
def GetMsgTransmitStorageGetName(self, messageName):
    return f"CANTX_{self.alias}_GetTxStorage_{messageName}"
def GetTxArrVarName(messageName):
    return f"g{messageName}_TX_ARR"
def GetTxArrLenName(self, messageName):
    return f"CANTX_{self.alias}_{messageName}_ARR_LEN"
def GetTxArrIdxName(self, messageName, muxIdx):
    return "0U" if muxIdx == "None" else f"CANTX_{self.alias}_{messageName}_M{muxIdx}_ARR_IDX"


# Transmit - setters
def GetSignalSetRawFromFrameName(self, signalName):
    return f"CANTX_{self.alias}_SetSRawFromFrame_{signalName}"
def GetSignalSetRawName(self, signalName):
    return f"CANTX_{self.alias}_SetSRaw_{signalName}"
def GetSignalSetFromFrameName(self, signalName):
    return f"CANTX_{self.alias}_SetSFromFrame_{signalName}"
def GetSignalSetName(self, signalName):
    return f"CANTX_{self.alias}_SetS_{signalName}"


# Receive - message ID helper getters
def GetRxNumMsg(self):
    return f"CANRX_{self.alias}_NUM_MESSAGES"
def GetMsgReceiveMidIdxGetName(self):
    return f"CANRX_{self.alias}_GetMidFromIdx"
def GetMsgReceiveMidIdxVarName():
    return "gMidFromIdx"


# Receive - storage
def GetLatestRxArrPtrName(messageName):
    return f"g{messageName}_LatestRxPtr"
def GetRxArrVarName(messageName):
    return f"g{messageName}_RX_ARR"
def GetRxArrLenName(self, messageName):
    return f"CANRX_{self.alias}_{messageName}_ARR_LEN"
def GetRxArrIdxName(self, messageName, muxIdx):
    return "0U" if muxIdx == "None" else f"CANRX_{self.alias}_{messageName}_M{muxIdx}_ARR_IDX"


# Receive - process and getters
def GetMsgProcessName(messageName):
    return f"CANRX_ProcessM_{messageName}"
def GetSignalGetRawFromFrameName(self, signalName):
    return f"CANRX_{self.alias}_GetSRawFromFrame_{signalName}"
def GetSignalGetRawName(self, signalName):
    return f"CANRX_{self.alias}_GetSRaw_{signalName}"
def GetSignalGetFromFrameName(self, signalName):
    return f"CANRX_{self.alias}_GetSFromFrame_{signalName}"
def GetSignalGetName(self, signalName):
    return f"CANRX_{self.alias}_GetS_{signalName}"


# Info
def GetMsgMidName(self, messageName):
    return f"CAN_{self.alias}_{messageName}_MID"
def GetMsgDlcName(self, messageName):
    return f"CAN_{self.alias}_{messageName}_DLC"
def GetMsgMaxMuxName(self, messageName):
    return f"CAN_{self.alias}_{messageName}_MAX_MUX_IDX"


def FLWI(line, indent=0):  # FormatLineWithIndent
    indentStr = "    " * indent
    line = indentStr + line.replace("\n", "\n" + indentStr).rstrip(" ")
    line = line.replace("\n" + indentStr + "\n", "\n\n").rstrip(" ")
    return line
