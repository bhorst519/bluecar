from helpers import *

#---------------------------------------------------------------------------------------------------
# Helper functions
#---------------------------------------------------------------------------------------------------
def GetCanTransmitInitFunction(alias):
    return f"bool CANTX_{alias}_Init(void)"

#---------------------------------------------------------------------------------------------------
# Code gen - header
#---------------------------------------------------------------------------------------------------
def PrintTransmitterHeader(self, messageInfo, signalInfo):
    alias = self.alias
    fileHandle = self.canTransmitterHeaderFileHandle
    GetMsgTransmitMuxIdxGetName = self.GetMsgTransmitMuxIdxGetName
    GetMsgTransmitStorageGetName = self.GetMsgTransmitStorageGetName
    GetSignalSetRawFromFrameName = self.GetSignalSetRawFromFrameName
    GetSignalSetRawName = self.GetSignalSetRawName
    GetSignalSetFromFrameName = self.GetSignalSetFromFrameName
    GetSignalSetName = self.GetSignalSetName


    PrintHeaderFileStart(fileHandle, "CAN_TRANSMITTER_H")

    # Includes
    PrintInclude(fileHandle, "stdbool.h")
    PrintInclude(fileHandle, "stdint.h")
    fileHandle.write("\n")

    # Storage private var getters
    PrintSubSectionHeader(fileHandle, "Transmit message storage getters")
    for message in messageInfo:
        messageName = message["name"]
        strToWrite = f"uint8_t * {GetMsgTransmitStorageGetName(messageName)}(const uint32_t muxIdx);\n"
        fileHandle.write(strToWrite)
    fileHandle.write("\n")

    # Mux index helper getters
    PrintSubSectionHeader(fileHandle, "Mux index getters for iteration")
    for message in messageInfo:
        messageName = message["name"]
        messageIsMuxed = message["muxer"] is not None
        if messageIsMuxed:
            strToWrite = f"uint32_t {GetMsgTransmitMuxIdxGetName(messageName)}(const uint32_t muxIdx);\n"
            fileHandle.write(strToWrite)
    fileHandle.write("\n")

    # Pack signal functions
    PrintSubSectionHeader(fileHandle, "Signal transmit setter functions")
    for signal in signalInfo:
        signalName = signal["name"]
        messageName = signal["message"]
        signalMuxIdx = signal["muxIdx"]
        rawType = signal["rawType"]
        convType = signal["convType"]
        thisSignalMessageInfo = [m for m in messageInfo if m["name"] == messageName][0]
        messageIsMuxed = thisSignalMessageInfo["muxer"] is not None
        generateFramePointerFuncs = not (signalMuxIdx is None and messageIsMuxed)  # Signal is in a muxed frame, or message isn't muxed
        strToWrite = f"// {signalName}\n"
        strToWrite += f"void {GetSignalSetRawFromFrameName(signalName)}(const {rawType} rawVal, uint8_t * const pData);\n"
        if generateFramePointerFuncs:
            strToWrite += f"void {GetSignalSetRawName(signalName)}(const {rawType} rawVal);\n"
        strToWrite += f"void {GetSignalSetFromFrameName(signalName)}(const {convType} converted, uint8_t * const pData);\n"
        if generateFramePointerFuncs:
            strToWrite += f"void {GetSignalSetName(signalName)}(const {convType} converted);\n"
        fileHandle.write(strToWrite + "\n")

    # Message transmit init
    PrintSubSectionHeader(fileHandle, "Message transmit init")
    fileHandle.write(GetCanTransmitInitFunction(alias) + ";\n\n")

    PrintHeaderFileEnd(fileHandle, "CAN_TRANSMITTER_H")


#---------------------------------------------------------------------------------------------------
# Code gen - source
#---------------------------------------------------------------------------------------------------
def PrintTransmitter(self, messageInfo, signalInfo):
    alias = self.alias
    fileHandle = self.canTransmitterFileHandle
    GetMsgDlcName = self.GetMsgDlcName
    GetMsgTransmitMuxIdxGetName = self.GetMsgTransmitMuxIdxGetName
    GetMsgTransmitStorageGetName = self.GetMsgTransmitStorageGetName
    GetSignalSetRawFromFrameName = self.GetSignalSetRawFromFrameName
    GetSignalSetRawName = self.GetSignalSetRawName
    GetSignalSetFromFrameName = self.GetSignalSetFromFrameName
    GetSignalSetName = self.GetSignalSetName
    GetTxArrIdxName = self.GetTxArrIdxName
    GetTxArrLenName = self.GetTxArrLenName


    """
    Signal-level functions
    """
    def PrintSignalConvertedSetter(signal, indent=1):
        signalName = signal["name"]
        rawType = signal["rawType"]
        convType = signal["convType"]
        setRawFromFrameName = GetSignalSetRawFromFrameName(signalName)
        convAppend = "F" if convType == "float" else "U" if convType.startswith("u") else ""
        min = str(signal["min"]) + convAppend
        max = str(signal["max"]) + convAppend
        strToWrite = f"const {convType} convertedSat = (converted > {max} ? {max} : (converted < {min} ? {min} : converted));\n"
        scale = str(signal["scale"]) + convAppend
        offset = str(signal["offset"]) + convAppend
        strToWrite += f"const {rawType} rawVal = ({rawType})((convertedSat - {offset}) / {scale});\n"
        strToWrite += f"{setRawFromFrameName}(rawVal, pData);\n"
        fileHandle.write(FLWI(strToWrite, indent))

    def PrintSignalRawSetterHelper(byte, shift, mask, shiftLeft):
        strToWrite = ""
        if mask == 0xFF:
            strToWrite += f"pData[{byte}] = (uint8_t)(" + GetShiftAndByteMask("rawVal", shift, mask, shiftLeft) + ");\n"
        else:
            maskHex = "0x{:02X}".format(mask)
            strToWrite += f"pData[{byte}] &= (uint8_t)(~{maskHex});\n"
            strToWrite += f"pData[{byte}] |= (uint8_t)(" + GetShiftAndByteMask("rawVal", shift, mask, shiftLeft) + ");\n"
        return strToWrite

    def PrintSignalRawSetter(signal, indent=1):
        startBit = signal["startBit"]
        bitLength = signal["bitLength"]
        endBit = startBit + bitLength - 1
        startByte = int(startBit / 8)
        endByte = int(endBit / 8)
        startLShift = startBit % 8
        startRShift = 8 - startLShift
        startByteMask = (0xFF << startLShift) & 0xFF
        endByteMask = (0xFF >> (7 - (endBit % 8)))

        strToWrite = ""
        if startByte == endByte:
            overallByteMask = startByteMask & endByteMask
            strToWrite += PrintSignalRawSetterHelper(startByte, startLShift, overallByteMask, True)
        else:
            strToWrite += PrintSignalRawSetterHelper(startByte, startLShift, startByteMask, True)
            rshift = startRShift
            for byte in range(startByte+1, endByte):
                strToWrite += PrintSignalRawSetterHelper(byte, rshift, 0xFF, False)
                rshift += 8
            strToWrite += PrintSignalRawSetterHelper(endByte, rshift, endByteMask, False)
        fileHandle.write(FLWI(strToWrite, indent))

    def PrintSignalTransmitter(signal):
        signalName = signal["name"]
        messageName = signal["message"]
        signalMuxIdx = signal["muxIdx"]
        rawType = signal["rawType"]
        convType = signal["convType"]
        thisSignalMessageInfo = [m for m in messageInfo if m["name"] == messageName][0]
        messageIsMuxed = thisSignalMessageInfo["muxer"] is not None
        generateFramePointerFuncs = not (signalMuxIdx is None and messageIsMuxed)  # Signal is in a muxed frame, or message isn't muxed
        # Set raw with a frame arg
        setRawFromFrameName = GetSignalSetRawFromFrameName(signalName)
        fileHandle.write(f"void  {setRawFromFrameName}(const {rawType} rawVal, uint8_t * const pData)\n{{\n")
        PrintSignalRawSetter(signal)
        fileHandle.write("}\n")
        # Set raw without a frame arg - requires a frame pointer
        if generateFramePointerFuncs:
            setRawName = GetSignalSetRawName(signalName)
            strToWrite = f"void {setRawName}(const {rawType} rawVal)\n{{\n"
            txArrVarName = GetTxArrVarName(messageName)
            txArrIdxName = GetTxArrIdxName(messageName, str(signalMuxIdx))
            strDataPtr = ""  # Save this, can be used below
            strDataPtr += FLWI(f"uint8_t * const pData = &{txArrVarName}[{txArrIdxName}][0U];\n", 1)
            strToWrite += strDataPtr + FLWI(f"{setRawFromFrameName}(rawVal, pData);\n", 1) + "}\n"
            fileHandle.write(strToWrite)
        # Set converted with a frame arg
        setFromFrameName = GetSignalSetFromFrameName(signalName)
        fileHandle.write(f"void {setFromFrameName}(const {convType} converted, uint8_t * const pData)\n{{\n")
        PrintSignalConvertedSetter(signal)
        fileHandle.write("}\n")
        # Set converted without a frame arg - requires a frame pointer
        if generateFramePointerFuncs:
            setName = GetSignalSetName(signalName)
            strToWrite = f"void {setName}(const {convType} converted)\n{{\n"
            strToWrite += strDataPtr + FLWI(f"{setFromFrameName}(converted, pData);\n", 1) + "}\n"
            fileHandle.write(strToWrite)
        fileHandle.write("\n")

    """
    Message-level functions
    """

    """
    Main file generation
    """
    # Includes
    PrintInclude(fileHandle, f"{alias}_canTransmitter.h")
    PrintInclude(fileHandle, f"{alias}_messageInfo.h")
    PrintInclude(fileHandle, "stdbool.h")
    PrintInclude(fileHandle, "stdint.h")
    fileHandle.write("\n")

    # Storage private vars
    PrintSubSectionHeader(fileHandle, "Transmit message storage")
    for message in messageInfo:
        messageName = message["name"]
        txArrVarName = GetTxArrVarName(messageName)
        messageTxArrLen = GetTxArrLenName(messageName)
        messageDlc = GetMsgDlcName(messageName)
        fileHandle.write(f"static uint8_t {txArrVarName}[{messageTxArrLen}][{messageDlc}];\n")
    fileHandle.write("\n")

    # Storage private var getters
    PrintSubSectionHeader(fileHandle, "Transmit message storage getters")
    for message in messageInfo:
        messageName = message["name"]
        messageIsMuxed = message["muxer"] is not None
        msgTransmitStorageGetName = GetMsgTransmitStorageGetName(messageName)
        txArrVarName = GetTxArrVarName(messageName)
        strToWrite = f"uint8_t * {msgTransmitStorageGetName}(const uint32_t muxIdx)\n"
        if messageIsMuxed:
            strToWrite += "{\n" + FLWI(f"return &{txArrVarName}[muxIdx][0U];\n", 1) + "}\n\n"
        else:
            strToWrite += "{\n" + FLWI("(void)muxIdx;\n", 1)
            strToWrite += FLWI(f"return &{txArrVarName}[0U][0U];\n", 1) + "}\n\n"
        fileHandle.write(strToWrite)

    # Mux index helper getters
    PrintSubSectionHeader(fileHandle, "Mux index getters for iteration")
    for message in messageInfo:
        messageName = message["name"]
        messageIsMuxed = message["muxer"] is not None
        transmitMuxIdxs = message["transmitMuxIdxs"]
        muxIdxArrVarName = GetMsgTransmitMuxIdxVarName(messageName)
        msgTransmitMuxIdxGetName = GetMsgTransmitMuxIdxGetName(messageName)
        if messageIsMuxed:
            strToWrite = f"uint32_t {muxIdxArrVarName}[] = {{\n"
            for muxIdx in transmitMuxIdxs:
                strToWrite += FLWI(f"{muxIdx}U,\n", 1)
            strToWrite += "};\n"
            strToWrite += f"uint32_t {msgTransmitMuxIdxGetName}(const uint32_t muxIdx)\n{{\n"
            strToWrite += FLWI(f"return {muxIdxArrVarName}[muxIdx];\n", 1)
            strToWrite += "}\n"
            fileHandle.write(strToWrite)
    fileHandle.write("\n")

    # Pack signal functions
    PrintSubSectionHeader(fileHandle, "Signal transmit setter functions")
    for signal in signalInfo:
        signalName = signal["name"]
        fileHandle.write(f"// {signalName}\n")
        PrintSignalTransmitter(signal)

    # Message transmit init
    PrintSubSectionHeader(fileHandle, "Message transmit init")
    fileHandle.write(GetCanTransmitInitFunction(alias) + "\n{\n")
    for message in messageInfo:
        messageName = message["name"]
        muxer = message["muxer"]
        transmitMuxIdxs = message["transmitMuxIdxs"]
        if muxer is not None:
            setFromFrameName = GetSignalSetFromFrameName(muxer)
            txArrVarName = GetTxArrVarName(messageName)
            fileHandle.write(FLWI(f"// {messageName}\n", 1))
            for muxIdx in transmitMuxIdxs:
                txArrIdxName = GetTxArrIdxName(messageName, str(muxIdx))
                fileHandle.write(FLWI(f"{setFromFrameName}({muxIdx}U, &{txArrVarName}[{txArrIdxName}][0U]);\n", 1))
            fileHandle.write("\n")

    # Return
    fileHandle.write(FLWI("return true;\n", 1) + "}\n")
