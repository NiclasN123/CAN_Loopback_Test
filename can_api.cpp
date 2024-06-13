#include "can_api.h"
#include <cstring>
#include <iostream>

TCAN_HANDLE CAN_Open(CHAR *ComPort, CHAR *szBitrate, CHAR *acceptance_code, CHAR *acceptance_mask, VOID *flags, DWORD Mode) {
    // Dummy implementation
    std::cout << "CAN_Open called with ComPort: " << ComPort << std::endl;
    return 1; // Dummy handle
}

TCAN_STATUS CAN_Close(TCAN_HANDLE Handle) {
    // Dummy implementation
    std::cout << "CAN_Close called" << std::endl;
    return CAN_ERR_OK;
}

TCAN_STATUS CAN_Flush(TCAN_HANDLE Handle) {
    // Dummy implementation
    std::cout << "CAN_Flush called" << std::endl;
    return CAN_ERR_OK;
}

TCAN_STATUS CAN_Write(TCAN_HANDLE Handle, CAN_MSG *Buf) {
    // Dummy implementation
    std::cout << "CAN_Write called" << std::endl;
    return CAN_ERR_OK;
}

TCAN_STATUS CAN_Read(TCAN_HANDLE Handle, CAN_MSG *Buf) {
    // Dummy implementation
    std::cout << "CAN_Read called" << std::endl;
    return CAN_ERR_OK;
}

TCAN_STATUS CAN_Version(TCAN_HANDLE Handle, CHAR *buf) {
    // Dummy implementation
    std::strcpy(buf, "1.0");
    std::cout << "CAN_Version called" << std::endl;
    return CAN_ERR_OK;
}