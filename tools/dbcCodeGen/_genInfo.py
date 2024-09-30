from helpers import *

#---------------------------------------------------------------------------------------------------
# Code gen
#---------------------------------------------------------------------------------------------------
def PrintMessageInfo(self, transmitMessageInfo, receiveMessageInfo):
    fileHandle = self.messageConstantsFileHandle
    GetMsgDlcName = self.GetMsgDlcName
    GetMsgMaxMuxName = self.GetMsgMaxMuxName
    GetMsgMidName = self.GetMsgMidName
    GetRxArrIdxName = self.GetRxArrIdxName
    GetRxArrLenName = self.GetRxArrLenName
    GetRxNumMsg = self.GetRxNumMsg
    GetTxArrIdxName = self.GetTxArrIdxName
    GetTxArrLenName = self.GetTxArrLenName


    def PrintRequiredMessageInfo(message):
        messageName = message["name"]
        fileHandle.write("// " + messageName + "\n")
        PrintDefine(fileHandle, GetMsgMidName(messageName), str(message["id"]))
        PrintDefine(fileHandle, GetMsgDlcName(messageName), str(message["length"]))

    PrintHeaderFileStart(fileHandle, "MESSAGE_INFO_H")
    PrintSubSectionHeader(fileHandle, "Transmit message info macros")
    for message in transmitMessageInfo:
        PrintRequiredMessageInfo(message)
        messageName = message["name"]
        transmitMuxIdxs = message["transmitMuxIdxs"]
        numMuxes = len(transmitMuxIdxs)
        PrintDefine(fileHandle, GetMsgMaxMuxName(messageName), str(max(0, (numMuxes - 1))))
        for idx, muxIdx in enumerate(transmitMuxIdxs):
            PrintDefine(fileHandle, GetTxArrIdxName(messageName, str(muxIdx)), str(idx))
        PrintDefine(fileHandle, GetTxArrLenName(messageName), str(max(1, numMuxes)))
        fileHandle.write("\n")

    PrintSubSectionHeader(fileHandle, "Receive message info macros")
    PrintDefine(fileHandle, GetRxNumMsg(), str(len(receiveMessageInfo)))
    fileHandle.write("\n")
    for message in receiveMessageInfo:
        PrintRequiredMessageInfo(message)
        messageName = message["name"]
        receiveMuxIdxs = message["receiveMuxIdxs"]
        numMuxes = len(receiveMuxIdxs)
        PrintDefine(fileHandle, GetMsgMaxMuxName(messageName), str(max(0, (numMuxes - 1))))
        for idx, muxIdx in enumerate(receiveMuxIdxs):
            PrintDefine(fileHandle, GetRxArrIdxName(messageName, str(muxIdx)), str(idx))
        PrintDefine(fileHandle, GetRxArrLenName(messageName), str(max(1, numMuxes)))
        fileHandle.write("\n")
    PrintHeaderFileEnd(fileHandle, "MESSAGE_INFO_H")
