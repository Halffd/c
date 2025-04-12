#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#include <tchar.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#define HANDLE int
#define INVALID_HANDLE_VALUE -1
#define BOOL int
#define FALSE 0
#define TRUE 1
#endif

void ListComPorts() {
#ifdef _WIN32
    HKEY hKey;
    LONG lRes;

    lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hKey);
    if (lRes != ERROR_SUCCESS) {
        printf("Erro ao abrir a chave do registro: %ld\n", lRes);
        return;
    }

    TCHAR valueName[256];
    DWORD valueNameSize = sizeof(valueName) / sizeof(valueName[0]);
    BYTE data[256];
    DWORD dataSize = sizeof(data);
    DWORD index = 0;

    while (RegEnumValue(hKey, index, valueName, &valueNameSize, NULL, NULL, data, &dataSize) == ERROR_SUCCESS) {
        printf("Porta encontrada: %s\n", data);
        valueNameSize = sizeof(valueName) / sizeof(valueName[0]);
        dataSize = sizeof(data);
        index++;
    }

    RegCloseKey(hKey);
#else
    printf("Listing serial ports is not directly supported on POSIX systems.\n");
    printf("Try using 'ls /dev/tty*' to list available ports.\n");
#endif
}

HANDLE openSerialPort(const char* comPortName) {
#ifdef _WIN32
    HANDLE hComm = CreateFile(comPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hComm == INVALID_HANDLE_VALUE) {
        printf("Error! - Port %s cannot be opened\n", comPortName);
    }
    return hComm;
#else
    int fd = open(comPortName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        printf("Error! - Port %s cannot be opened\n", comPortName);
    }
    return fd;
#endif
}

void closeSerialPort(HANDLE hComm) {
#ifdef _WIN32
    CloseHandle(hComm);
#else
    close(hComm);
#endif
}

BOOL configureSerialPort(HANDLE hComm) {
#ifdef _WIN32
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hComm, &dcbSerialParams)) {
        printf("Error in GetCommState()");
        return FALSE;
    }

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hComm, &dcbSerialParams)) {
        printf("Error in setting DCB structure");
        return FALSE;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hComm, &timeouts)) {
        printf("Error in setting timeouts");
        return FALSE;
    }
    return TRUE;
#else
    struct termios options;
    if (tcgetattr(hComm, &options) != 0) {
        printf("Error in getting termios attributes\n");
        return FALSE;
    }

    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    options.c_cc[VMIN] = 1;
    options.c_cc[VTIME] = 5;

    if (tcsetattr(hComm, TCSANOW, &options) != 0) {
        printf("Error in setting termios attributes\n");
        return FALSE;
    }
    return TRUE;
#endif
}

int readFromPort(const char* comPortName) {
    HANDLE hComm = openSerialPort(comPortName);
    if (hComm == INVALID_HANDLE_VALUE) {
        return 1;
    }

    if (!configureSerialPort(hComm)) {
        closeSerialPort(hComm);
        return 1;
    }

#ifdef _WIN32
    DWORD dwEventMask;
    char TempChar;
    char SerialBuffer[2560];
    DWORD NoBytesRead;
#else
    char SerialBuffer[2560];
    int NoBytesRead;
#endif

    printf("Waiting for data reception...\n");

    while (TRUE) {
#ifdef _WIN32
        WaitCommEvent(hComm, &dwEventMask, NULL);
        ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
        if (NoBytesRead > 0) {
            SerialBuffer[0] = TempChar;
            SerialBuffer[1] = '\0';
            printf("Received: %s", SerialBuffer);
        }
#else
        NoBytesRead = read(hComm, SerialBuffer, sizeof(SerialBuffer) - 1);
        if (NoBytesRead > 0) {
            SerialBuffer[NoBytesRead] = '\0';
            printf("Received: %s", SerialBuffer);
        }
#endif
    }

    closeSerialPort(hComm);
    return 0;
}

int writeToPort(const char* comPortName) {
    HANDLE hComm = openSerialPort(comPortName);
    if (hComm == INVALID_HANDLE_VALUE) {
        return 1;
    }

    if (!configureSerialPort(hComm)) {
        closeSerialPort(hComm);
        return 1;
    }

    printf("Write data to port and press Enter...\n");

    while (TRUE) {
        char lpBuffer[100];
        fgets(lpBuffer, sizeof(lpBuffer), stdin);

#ifdef _WIN32
        DWORD dNoOfBytesWritten;
        WriteFile(hComm, lpBuffer, strlen(lpBuffer), &dNoOfBytesWritten, NULL);
#else
        write(hComm, lpBuffer, strlen(lpBuffer));
#endif
    }

    closeSerialPort(hComm);
    return 0;
}

int serial(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s [list|read COMx|write COMx]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "list") == 0) {
        ListComPorts();
    } else if (strcmp(argv[1], "read") == 0 && argc == 3) {
        readFromPort(argv[2]);
    } else if (strcmp(argv[1], "write") == 0 && argc == 3) {
        writeToPort(argv[2]);
    } else {
        printf("Argumento inválido. Uso: %s [list|read COMx|write COMx]\n", argv[0]);
        return 1;
    }

    return 0;
}