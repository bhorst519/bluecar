import os, re


def RemoveSuffix(string, suffix):
    if string.endswith(suffix):
        string = string[:-len(suffix)]
    return string


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
        "maxMuxIdx": -1,
        "cycleTime": 0,
    }


RE_SEARCH_SIGNAL_INFO = "(?<=^ SG_) (\S+) ((\S+) )*: (\d+)\|(\d+)@([01])([+-]) \(([-\d\.e]+),([-\d\.e]+)\) \[([-\d\.e]+)\|([-\d\.e]+)\] \"(.*)\""
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
    units = regexSignalInfo.group(12)
    isMuxer = signalMux == "M"
    muxedSignal = signalMux is not None and not isMuxer
    bitLength = int(signalBitLength)
    signed = False if (signalSignedness == "+") else True
    scale = GetNumberFromString(signalScale)
    offset = GetNumberFromString(signalOffset)
    min = GetNumberFromString(signalMin)
    max = GetNumberFromString(signalMax)
    anyFloat = any([type(v) is float for v in [scale, offset, min, max]])
    signedConvertedValue = signed or offset < 0
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
        "SNA": None,
        "units": units,
        # Unsigned integer type to pack into/unpack from raw bytes
        "rawType": GetRawTypeFromBitLength(bitLength),
        # Integer type representing scaled/offset signal before packing/unpacking
        "convIntType": GetIntTypeFromBitLength(bitLength, signed),
        # Converted underlying type
        "convType": GetTypeFromSignAndConv(bitLength, signedConvertedValue, scale, offset),
    }


RE_SEARCH_SIGNAL_VAL_TABLE_INFO = "(?<=^VAL_) (\d+) (\S+)(.*) ;"
RE_SEARCH_SIGNAL_VAL_ENTRY      = "(?<=^ )(\d+) \"(\S+)\"(.*)"
def GetSignalValTableInfo(regexSigValInfo):
    signalName = regexSigValInfo.group(2)
    # messageId = regexSigValInfo.group(1)
    entries = regexSigValInfo.group(3)

    # Recursive function to extract all value table entries
    def ExtractVal(valStr, valDict):
        regexValEntry = re.search(RE_SEARCH_SIGNAL_VAL_ENTRY, valStr)
        if regexValEntry is not None:
            value = regexValEntry.group(1)
            description = regexValEntry.group(2)
            next = regexValEntry.group(3)
            if description in valDict:
                raise Exception(f"Duplicate value {description} in value table for signal {signalName}")
            valDict.update({description.upper(): int(value)})
            if next:
                ExtractVal(next, valDict)
    valDict = {}
    ExtractVal(entries, valDict)

    return {
        "signal": signalName,
        "valueTable": valDict,
    }


RE_SEARCH_SIGNAL_MSG_CYCLE_TIME_INFO = "(?<=^BA_ \"GenMsgCycleTime\" BO_) (\d+) (\d+)"
def GetMessageCycleTimeInfo(regexCycleTimeInfo):
    messageId = regexCycleTimeInfo.group(1)
    cycleTime = regexCycleTimeInfo.group(2)
    return {
        "id": int(messageId),
        "cycleTime": int(cycleTime),
    }
