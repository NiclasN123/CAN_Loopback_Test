#include <iostream>
#include <cstring>  // Für memset in C++
#include "can_api.h"  // Ihre CAN-Bibliothek, angepasst für C++

int main() {
    TCAN_HANDLE Handle;
    TCAN_STATUS Status;
    CHAR ComPort[] = "/dev/ttyUSB0";
    CHAR szBitrate[] = "800";
    CHAR acceptance_code[] = "1FFFFFFF";
    CHAR acceptance_mask[] = "00000000";
    VOID* flags = CAN_TIMESTAMP_OFF;
    DWORD Mode = LoopBack;
    char version[10];
    CAN_MSG SendMSG;
    CAN_MSG RecvMSG;

    Handle = -1;
    Status = 0;

    // Konfiguration der Sendenachricht
    SendMSG.Flags = CAN_FLAGS_EXTENDED;
    SendMSG.Id = 0x12345678;
    SendMSG.Size = 8;
    SendMSG.Data[0] = 0x11;
    SendMSG.Data[1] = 0x22;
    SendMSG.Data[2] = 0x33;
    SendMSG.Data[3] = 0x44;
    SendMSG.Data[4] = 0x55;
    SendMSG.Data[5] = 0x66;
    SendMSG.Data[6] = 0x77;
    SendMSG.Data[7] = 0x88;

    // CAN-Port öffnen für Senden und Empfangen
    Handle = CAN_Open(ComPort, szBitrate, acceptance_code, acceptance_mask, flags, Mode);
    std::cout << "Handle= " << Handle << std::endl;

    // Überprüfen, ob das Öffnen des Ports erfolgreich war
    if (Handle < 0) {
        return 0;
    }

    // Puffer leeren und Versionsinformation abrufen
    std::memset(version, 0, sizeof(char) * 10);
    Status = CAN_Flush(Handle);
    Status = CAN_Version(Handle, version);

    // Ausgabe der Version, falls erfolgreich
    if (Status == CAN_ERR_OK) {
        std::cout << "Version : " << version << std::endl;
    }

    // Nachricht senden
    Status = CAN_Write(Handle, &SendMSG);
    if (Status == CAN_ERR_OK) {
        std::cout << "Write Success" << std::endl;
    }

    // Hauptschleife für die Benutzereingabe und CAN-Kommunikation
    while (true) {
        Status = CAN_Read(Handle, &RecvMSG);
        if (Status == CAN_ERR_OK) {
            std::cout << "Read ID=0x" << std::hex << RecvMSG.Id
                      << ", Type=" << ((RecvMSG.Flags & CAN_FLAGS_STANDARD) ? "STD" : "EXT")
                      << ", DLC=" << std::hex << RecvMSG.Size
                      << ", FrameType=" << ((RecvMSG.Flags & CAN_FLAGS_REMOTE) ? "REMOTE" : "DATA")
                      << ", Data=";

            for (int i = 0; i < RecvMSG.Size; ++i) {
                std::cout << std::hex << (int)RecvMSG.Data[i] << ",";
            }
            std::cout << std::endl;
            break;  // Wir brechen die Schleife nach dem ersten Lesen ab
        }
    }

    // CAN-Port schließen
    Status = CAN_Close(Handle);
    std::cout << "Test finish" << std::endl;

    return 0;
}