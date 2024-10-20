from helpers import *

#---------------------------------------------------------------------------------------------------
# Helper functions
#---------------------------------------------------------------------------------------------------
def GetCanReceiveFunction(alias):
    return f"bool CANRX_{alias}_Receive(const uint16_t mid, const uint8_t dlc, const uint8_t * const pData)"

#---------------------------------------------------------------------------------------------------
# Code gen - header
#---------------------------------------------------------------------------------------------------
def PrintReceiverHeader(self, signalInfo):
    alias = self.alias
    fileHandle = self.canReceiverHeaderFileHandle
    GetMsgReceiveMidIdxGetName = self.GetMsgReceiveMidIdxGetName
    GetSignalGetRawFromFrameName = self.GetSignalGetRawFromFrameName
    GetSignalGetRawName = self.GetSignalGetRawName
    GetSignalGetFromFrameName = self.GetSignalGetFromFrameName
    GetSignalGetName = self.GetSignalGetName


    PrintHeaderFileStart(fileHandle, "CAN_RECEIVER_H")

    # Includes
    PrintInclude(fileHandle, "stdbool.h")
    PrintInclude(fileHandle, "stdint.h")
    fileHandle.write("\n")

    # Message ID helper getters
    PrintSubSectionHeader(fileHandle, "Receive message ID getters for iteration")
    strToWrite = f"uint32_t {GetMsgReceiveMidIdxGetName()}(const uint32_t muxIdx);\n\n"
    fileHandle.write(strToWrite)

    # Unpack signal functions
    PrintSubSectionHeader(fileHandle, "Signal receive unpack functions")
    for signal in signalInfo:
        signalName = signal["name"]
        rawType = signal["rawType"]
        convType = signal["convType"]

        strToWrite = f"// {signalName}\n"
        strToWrite += f"{rawType} {GetSignalGetRawFromFrameName(signalName)}(const uint8_t * const pData);\n"
        strToWrite += f"{rawType} {GetSignalGetRawName(signalName)}(void);\n"
        strToWrite += f"{convType} {GetSignalGetFromFrameName(signalName)}(const uint8_t * const pData);\n"
        strToWrite += f"{convType} {GetSignalGetName(signalName)}(void);\n"
        fileHandle.write(strToWrite + "\n")

    # Message receive hook
    PrintSubSectionHeader(fileHandle, "Message receive hook")
    fileHandle.write(GetCanReceiveFunction(alias) + ";\n\n")

    PrintHeaderFileEnd(fileHandle, "CAN_RECEIVER_H")


#---------------------------------------------------------------------------------------------------
# Code gen - source
#---------------------------------------------------------------------------------------------------
def PrintReceiver(self, messageInfo, signalInfo):
    alias = self.alias
    fileHandle = self.canReceiverFileHandle
    GetMsgDlcName = self.GetMsgDlcName
    GetMsgMidName = self.GetMsgMidName
    GetMsgReceiveMidIdxGetName = self.GetMsgReceiveMidIdxGetName
    GetRxArrIdxName = self.GetRxArrIdxName
    GetRxArrLenName = self.GetRxArrLenName
    GetSignalGetRawFromFrameName = self.GetSignalGetRawFromFrameName
    GetSignalGetRawName = self.GetSignalGetRawName
    GetSignalGetFromFrameName = self.GetSignalGetFromFrameName
    GetSignalGetName = self.GetSignalGetName


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
        strToWrite = f"{convIntType} raw = ({convIntType}){getRawFromFrameName}(pData);\n"
        if signed:
            # Signed integer - use sign-extended raw
            bitsToShift = BIT_LENGTH_FROM_TYPE[convIntType] - bitLength
            if bitsToShift > 0:
                strToWrite += "// Sign extend\n"
                strToWrite += f"raw = (raw << {bitsToShift}) >> {bitsToShift};\n"
        convAppend = "F" if convType == "float" else "U" if convType.startswith("u") else ""
        scale = str(signal["scale"]) + convAppend
        offset = str(signal["offset"]) + convAppend
        strToWrite += f"{convType} converted = ((({convType})raw) * {scale}) + {offset};\n"
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
        strToWrite = f"const {rawType} rawVal = "
        if startByte == endByte:
            overallByteMask = startByteMask & endByteMask
            strToWrite += GetByteMaskAndShift(f"pData[{startByte}]", overallByteMask, startRShift, False) + ";\n"
        else:
            strToWrite += GetByteMaskAndShift(f"pData[{startByte}]", startByteMask, startRShift, False)
            lshift = startLShift
            for byte in range(startByte+1, endByte):
                strToWrite += " + " + GetByteMaskAndShift(f"pData[{byte}]", 0xFF, lshift)
                lshift += 8
            strToWrite += " + " + GetByteMaskAndShift(f"pData[{endByte}]", endByteMask, lshift) + ";\n"
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
        fileHandle.write(f"{rawType} {getRawFromFrameName}(const uint8_t * const pData)\n{{\n")
        PrintSignalRawUnpacker(signal)
        fileHandle.write("}\n")
        # Unpack raw without a frame arg - requires a frame pointer
        getRawName = GetSignalGetRawName(signalName)
        strToWrite = f"{rawType} {getRawName}(void)\n{{\n"
        strDataPtr = ""  # Save this, can be used below
        if signalMuxIdx is None and messageIsMuxed:
            latestRxArrPtrName = GetLatestRxArrPtrName(messageName)
            strDataPtr += FLWI("// This signal belongs to a muxed message but is static. Get contents from latest-received frame\n", 1)
            strDataPtr += FLWI(f"const uint8_t * const pData = {latestRxArrPtrName};\n", 1)
        else:
            rxArrVarName = GetRxArrVarName(messageName)
            rxArrIdxName = GetRxArrIdxName(messageName, str(signalMuxIdx))
            strDataPtr += FLWI(f"const uint8_t * const pData = &{rxArrVarName}[{rxArrIdxName}][0U];\n", 1)
        strToWrite += strDataPtr + FLWI(f"return {getRawFromFrameName}(pData);\n", 1) + "}\n"
        fileHandle.write(strToWrite)
        # Unpack converted with a frame arg
        getFromFrameName = GetSignalGetFromFrameName(signalName)
        fileHandle.write(f"{convType} {getFromFrameName}(const uint8_t * const pData)\n{{\n")
        PrintSignalConvertedUnpacker(signal)
        fileHandle.write("}\n")
        # Unpack converted without a frame arg - requires a frame pointer
        getName = GetSignalGetName(signalName)
        strToWrite = f"{convType} {getName}(void)\n{{\n"
        strToWrite += strDataPtr + FLWI(f"return {getFromFrameName}(pData);\n", 1) + "}\n\n"
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
        strToWrite += FLWI(f"{latestRxArrPtrName} = &{rxArrVarName}[{rxArrIdxName}][0U];\n", indent)
        fileHandle.write(strToWrite)

    def PrintMessageReceiver(message):
        messageName = message["name"]
        muxer = message["muxer"]
        thisMessageSignalInfo = [s for s in signalInfo if s["message"] == messageName]

        # Private function
        fileHandle.write(f"static bool {GetMsgProcessName(messageName)}(const uint8_t * const pData)\n{{\n")
        fileHandle.write(FLWI("bool success = true;\n", 1))

        if muxer is not None:
            getRawFromFrameName = GetSignalGetRawFromFrameName(muxer)
            fileHandle.write(FLWI(f"const uint32_t muxIdx = {getRawFromFrameName}(pData);\n\n", 1))
            # Get the unique muxes for this message
            uniqueMuxes = list(set([s["muxIdx"] for s in thisMessageSignalInfo if s["muxIdx"] is not None]))
            # Switch on mux
            fileHandle.write(FLWI("switch (muxIdx)\n{\n", 1))
            for mux in uniqueMuxes:
                # Get the signals for this mux
                thisMuxSignalInfo = [s for s in thisMessageSignalInfo if s["muxIdx"] == mux]
                fileHandle.write(FLWI(f"case {mux}U:\n{{\n", 2))
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
        strToWrite += FLWI(f"for (uint32_t d = 0U; d < {messageDlc}; ++d)\n{{\n", 2)
        strToWrite += FLWI(f"{latestRxArrPtrName}[d] = pData[d];\n", 3)
        strToWrite += FLWI("}\n", 2) + FLWI("}\n\n", 1)
        fileHandle.write(strToWrite)

        # Return
        fileHandle.write(FLWI("return success;\n", 1) + "}\n\n")

    """
    Main file generation
    """
    # Includes
    PrintInclude(fileHandle, f"{alias}_canReceiver.h")
    PrintInclude(fileHandle, f"{alias}_messageInfo.h")
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
        fileHandle.write(f"static uint8_t {rxArrVarName}[{messageRxArrLen}][{messageDlc}];\n")
        latestRxArrPtrName = GetLatestRxArrPtrName(messageName)
        fileHandle.write(f"static uint8_t * {latestRxArrPtrName} = &{rxArrVarName}[0U][0U];\n")
    fileHandle.write("\n")

    # Message ID helper getters
    PrintSubSectionHeader(fileHandle, "Receive message ID getters for iteration")
    msgReceiveMidIdxVarName = GetMsgReceiveMidIdxVarName()
    strToWrite = f"uint32_t {msgReceiveMidIdxVarName}[] = {{\n"
    for message in messageInfo:
        messageName = message["name"]
        strToWrite += FLWI(f"{GetMsgMidName(messageName)},\n", 1)
    strToWrite += "};\n"
    strToWrite += f"uint32_t {GetMsgReceiveMidIdxGetName()}(const uint32_t msgIdx)\n{{\n"
    strToWrite += FLWI(f"return {msgReceiveMidIdxVarName}[msgIdx];\n", 1)
    strToWrite += "}\n"
    fileHandle.write(strToWrite)

    # Unpack signal functions
    PrintSubSectionHeader(fileHandle, "Signal receive unpack functions")
    for signal in signalInfo:
        signalName = signal["name"]
        fileHandle.write(f"// {signalName}\n")
        PrintSignalReceiver(signal)

    # Unpack message private functions
    PrintSubSectionHeader(fileHandle, "Message receive storage functions")
    for message in messageInfo:
        PrintMessageReceiver(message)

    # Message receive hook
    PrintSubSectionHeader(fileHandle, "Message receive hook")
    fileHandle.write(GetCanReceiveFunction(alias) + "\n{\n")
    fileHandle.write(FLWI("bool success = true;\n\n", 1))
    # Switch on message ID
    fileHandle.write(FLWI("switch (mid)\n{\n", 1))
    for message in messageInfo:
        messageName = message["name"]
        strToWrite = ""
        strToWrite += FLWI(f"case {GetMsgMidName(messageName)}:\n{{\n", 2)
        strToWrite += FLWI(f"if (dlc != {GetMsgDlcName(messageName)})\n{{\n", 3) + FLWI("success = false;\n", 4) + FLWI("}\n", 3)
        strToWrite += FLWI("else\n{\n", 3) + FLWI(f"success = {GetMsgProcessName(messageName)}(pData);\n", 4) + FLWI("}\nbreak;\n", 3)
        strToWrite += FLWI("}\n", 2)
        fileHandle.write(strToWrite)
    strToWrite = ""
    strToWrite += FLWI("default:\n{\n", 2) + FLWI("success = false;\nbreak;\n", 3) + FLWI("}\n", 2)
    strToWrite += FLWI("}\n\n", 1)
    fileHandle.write(strToWrite)

    # Return
    fileHandle.write(FLWI("return success;\n", 1) + "}\n")
