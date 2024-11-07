#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

void ListComPorts() {
    HKEY hKey;
    LONG lRes;

    // Abre a chave do registro onde as portas COM estão listadas
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

    // Enumerar os valores da chave
    while (RegEnumValue(hKey, index, valueName, &valueNameSize, NULL, NULL, data, &dataSize) == ERROR_SUCCESS) {
        printf("Porta encontrada: %s\n", valueName);
        valueNameSize = sizeof(valueName) / sizeof(valueName[0]); // Resetar o tamanho
        dataSize = sizeof(data); // Resetar o tamanho
        index++;
    }

    // Fecha a chave do registro
    RegCloseKey(hKey);
}

int readFromPort(char* comPortName) {
    HANDLE hComm;
    BOOL Status;
    DWORD dwEventMask;
    char TempChar;
    char SerialBuffer[2560];
    DWORD NoBytesRead;
    int i = 0;

    printf("\n\n +====================================+");
    printf("\n | Recepcao por porta serial         |");
    printf("\n +====================================+\n");

    /*--------- Opening the serial port -------------*/
    hComm = CreateFile(comPortName, // Name of the port
                       GENERIC_READ | GENERIC_WRITE, // Read/Write mode
                       0, // No sharing
                       NULL, // No security
                       OPEN_EXISTING, // Open existing port
                       0, // No overlapped I/O
                       NULL); // No template

    if (hComm == INVALID_HANDLE_VALUE) {
        printf("\n Error! - Port %s cannot be opened\n", comPortName);
        return 1; // Exit the program on failure
    } else {
        printf("\n Port %s opened\n", comPortName);
    }

    /*--- Configuring the serial port parameters -----*/
    DCB dcbSerialParams = {0}; // Initialize DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    Status = GetCommState(hComm, &dcbSerialParams); // Get current state
    if (!Status) {
        printf("\n Error in GetCommState()");
        CloseHandle(hComm);
        return 1; // Exit on failure
    }

    dcbSerialParams.BaudRate = CBR_115200; // Set baud rate
    dcbSerialParams.ByteSize = 8; // Set byte size to 8
    dcbSerialParams.StopBits = ONESTOPBIT; // Set stop bits to 1
    dcbSerialParams.Parity = NOPARITY; // No parity

    Status = SetCommState(hComm, &dcbSerialParams); // Apply settings
    if (!Status) {
        printf("\n Error in setting DCB structure");
        CloseHandle(hComm);
        return 1; // Exit on failure
    } else {
        printf("\n Baudrate = %d", dcbSerialParams.BaudRate);
        printf("\n ByteSize = %d", dcbSerialParams.ByteSize);
        printf("\n StopBits = %d", dcbSerialParams.StopBits);
        printf("\n Parity = %d", dcbSerialParams.Parity);
    }

    /*------ Setting timeouts --------------*/
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hComm, &timeouts)) {
        printf("\n Error in setting timeouts");
        CloseHandle(hComm);
        return 1; // Exit on failure
    }

    /*--------- Setting the mask for reception -----------------*/
    Status = SetCommMask(hComm, EV_RXCHAR); // Configure Windows to monitor the serial port
    if (!Status) {
        printf("\n Error in setting CommMask");
        CloseHandle(hComm);
        return 1; // Exit on failure
    } else {
        printf("\n\n Waiting for data reception\n\n...");
    }

    while (1) {
        /*------------ Waiting for data -----------------------*/
        Status = WaitCommEvent(hComm, &dwEventMask, NULL); // Wait for a character

        if (!Status) {
            printf("\n Error in WaitCommEvent()");
            break; // Exit loop on failure
        } else {
            i = 0;

            do {
                Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
                if (Status && NoBytesRead > 0) {
                    SerialBuffer[i++] = TempChar;
                }
            } while (NoBytesRead > 0 && i < sizeof(SerialBuffer) - 1); // Prevent buffer overflow

            SerialBuffer[i] = '\0'; // Null-terminate the string

            /*------------ Print the received string ----------------------*/
            printf("\n Received: %s", SerialBuffer);
        }
    }

    CloseHandle(hComm); // Close the serial port
    printf("\n +=================================+\n");
    return 0;
}

int writeToPort(char* comPortName) {
    HANDLE hComm;
    BOOL Status;

    printf("\n\n +==========================================+");
    printf("\n | Transmissao Serial |");
    printf("\n +==========================================+\n");

    /*--------- Opening the serial port -------------*/
    hComm = CreateFile(
        comPortName,              // Name of the port
        GENERIC_READ | GENERIC_WRITE, // Read/Write mode
        0,                         // No sharing
        NULL,                      // No security
        OPEN_EXISTING,            // Opens existing port
        0,                         // No overlap
        NULL                       // No template
    );

    if (hComm == INVALID_HANDLE_VALUE) {
        printf("\n Erro! - Port %s nao pode ser aberta\n", comPortName);
        return 1; // Exit if the port cannot be opened
    } else {
        printf("\n Porta %s aberta\n", comPortName);
    }

    /*--- Setting serial port parameters -----*/
    DCB dcbSerialParams = { 0 }; // Initialize DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    Status = GetCommState(hComm, &dcbSerialParams); // Get current state
    if (Status == FALSE) {
        printf("\n Erro! em ajustar GetCommState()");
        CloseHandle(hComm);
        return 1; // Exit if getting state fails
    }

    dcbSerialParams.BaudRate = CBR_115200; // Set Baud Rate to 115200
    dcbSerialParams.ByteSize = 8;           // Data byte size
    dcbSerialParams.StopBits = ONESTOPBIT;  // 1 Stop bit
    dcbSerialParams.Parity = NOPARITY;      // No parity

    Status = SetCommState(hComm, &dcbSerialParams); // Configure the port
    if (Status == FALSE) {
        printf("\n Erro! ao ajustar estrutura DCB");
        CloseHandle(hComm);
        return 1; // Exit if setting state fails
    } else {
        // If successful, display the configured values
        printf("\n Baudrate = %d", dcbSerialParams.BaudRate);
        printf("\n ByteSize = %d", dcbSerialParams.ByteSize);
        printf("\n StopBits = %d", dcbSerialParams.StopBits);
        printf("\n Parity = %d", dcbSerialParams.Parity);
    }

    /*------ Setting timeouts --------------*/
    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm, &timeouts) == FALSE) {
        printf("\n Erro em ajustar TimeOuts");
        CloseHandle(hComm);
        return 1; // Exit if setting timeouts fails
    } else {
        printf("\n\n Escreva dados para a porta e tecle Enter\n\n... ");
    }

    while (1) {
        char lpBuffer[100];
        fgets(lpBuffer, sizeof(lpBuffer), stdin); // Receive string from user

        /*---------- Writing characters to the serial port -----------------------*/
        DWORD dNoOFBytestoWrite = strlen(lpBuffer); // Calculate bytes to write
        DWORD dNoOfBytesWritten = 0; // Number of bytes written

        Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
        if (Status == TRUE) {
            printf("\n %s \n", lpBuffer); // Print data written to the port
        } else {
            printf("\n\n Erro %d ao escrever na porta serial", GetLastError());
        }
    }

    CloseHandle(hComm);
    printf("\n=================================\n");
    return 0;
}
int testOpen() {
    HANDLE hComm;

    hComm = CreateFile("COM1",               // Port name
                       GENERIC_READ | GENERIC_WRITE, // Read/Write access
                       0,                         // No sharing
                       NULL,                      // No security
                       OPEN_EXISTING,            // Open existing port
                       0,                         // No overlap
                       NULL);                    // Null for serial port

    if (hComm == INVALID_HANDLE_VALUE) {
        printf("Error opening serial port\n");
        return 1; // Return an error code
    } else {
        printf("Successfully opened serial port\n");
    }

    CloseHandle(hComm); // Close serial port
    return 0; // Success
}
int pergunta(void) {
    HANDLE hComm;
    char ComPortName[] = "COM3"; // Nome da porta a ser aberta.
    BOOL Status;

    printf("\n\n +==========================================+");
    printf("\n | Transmissao Serial |");
    printf("\n +==========================================+\n");

    /*--------- Abrindo a porta serial -------------*/
    hComm = CreateFile(ComPortName, // Nome da porta
                       GENERIC_READ | GENERIC_WRITE, // Modo leitura/escrita
                       0, // Sem compartilhamento
                       NULL, // Sem segurança
                       OPEN_EXISTING, // Abre somente a porta existente
                       0, // Sem sobreposição de E/S
                       NULL); // Null para porta serial

    if (hComm == INVALID_HANDLE_VALUE) {
        printf("\n Erro! - Port %s nao pode ser aberta\n", ComPortName);
        return 1; // Sai do programa em caso de erro
    } else {
        printf("\n Porta %s aberta\n", ComPortName);
    }

    /*--- Ajustando os parâmetros para a porta serial -----*/
    DCB dcbSerialParams = {0}; // Inicializando a estrutura DCB
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    Status = GetCommState(hComm, &dcbSerialParams); // Recebendo o estado corrente

    if (Status == FALSE) {
        printf("\n Erro! em ajustar GetCommState()");
        CloseHandle(hComm);
        return 1; // Sai do programa em caso de erro
    }

    dcbSerialParams.BaudRate = CBR_115200; // Ajustando Baud Rate = 115200
    dcbSerialParams.ByteSize = 8; // Tamanho do byte de dados
    dcbSerialParams.StopBits = ONESTOPBIT; // Ajustando stop bits = 1
    dcbSerialParams.Parity = NOPARITY; // Ajustando sem paridade

    Status = SetCommState(hComm, &dcbSerialParams); // Configurando a porta de acordo com os ajustes em DCB
    if (Status == FALSE) {
        printf("\n Erro! ao ajustar estrutura DCB");
        CloseHandle(hComm);
        return 1; // Sai do programa em caso de erro
    }

    // Se houve sucesso, mostra os valores ajustados
    printf("\n Baudrate = %d", dcbSerialParams.BaudRate);
    printf("\n ByteSize = %d", dcbSerialParams.ByteSize);
    printf("\n StopBits = %d", dcbSerialParams.StopBits);
    printf("\n Parity = %d", dcbSerialParams.Parity);

    /*------ Ajustando timeouts --------------*/
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm, &timeouts) == FALSE) {
        printf("\n Erro em ajustar TimeOuts");
        CloseHandle(hComm);
        return 1; // Sai do programa em caso de erro
    } else {
        printf("\n\n Escreva dados para a porta e tecle Enter\n\n... ");
    }

    /*--------- Ajustando a máscara para receber ---------------*/
    Status = SetCommMask(hComm, EV_RXCHAR); // Configura Windows para monitorar a porta serial
    if (Status == FALSE) {
        printf("\n\n Erro! em ajustar CommMask");
        CloseHandle(hComm);
        return 1; // Sai do programa em caso de erro
    }

    while (1) {
        char lpBuffer[100];
        fgets(lpBuffer, 100, stdin); // Recebe string do usuário

        /*---------- Escrevendo caracteres para a porta serial -----------------------*/
        DWORD dNoOFBytestoWrite = strlen(lpBuffer); // Número de bytes a escrever
        DWORD dNoOfBytesWritten = 0; // Número de bytes escritos

        Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
        if (Status == TRUE) {
            // printf("\n %s \n", lpBuffer); // Imprime dados escritos na porta
        } else {
            printf("\n\n Erro %d ao escrever na porta serial", GetLastError());
        }

        DWORD dwEventMask; // Máscara de evento para capturar
        DWORD NoBytesRead; // Bytes lidos pela função ReadFile()
        int i = 0;

        Status = WaitCommEvent(hComm, &dwEventMask, NULL); // Aguarda por caractere

        /*-------- Programa aguarda aqui até o caractere ser recebido ------------*/
        char TempChar; // Caractere temporário
        char SerialBuffer[2560]; // Buffer contendo dados recebidos

        if (Status == FALSE) {
            printf("\n Erro ao ajustar WaitCommEvent()");
        } else {
            i = 0;
            do {
                Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
                SerialBuffer[i++] = TempChar;
            } while (NoBytesRead > 0);

            /*------------ Imprime a string lida ----------------------*/
            printf("\n ");
            for (int j = 0; j < i - 1; j++) { // j < i-1 para remover o último caractere duplicado
                printf("%c", SerialBuffer[j]);
            }
        }
    }

    CloseHandle(hComm);
    printf("\n ===================================\n");
    return 0; // Sai do programa com sucesso
}
int perguntaLeitura(void) {
    HANDLE hComm;
    char ComPortName[] = "COM2"; // Nome da porta a ser aberta
    BOOL Status; // Estado de operações
    DWORD dwEventMask; // Máscara de evento para capturar
    char TempChar; // Caractere temporário
    char SerialBuffer[2560]; // Buffer contendo dados recebidos
    DWORD NoBytesRead; // Bytes lidos pela função ReadFile()
    int i = 0;
    char lpBuffer[100];

    printf("\n\n +====================================+");
    printf("\n | Recepcao por porta serial |");
    printf("\n +===================================+\n");

    /*--------- Abrindo a porta serial -------------*/
    hComm = CreateFile(ComPortName, // Nome da porta
                       GENERIC_READ | GENERIC_WRITE, // Modo leitura/escrita
                       0, // Sem compartilhamento
                       NULL, // Sem segurança
                       OPEN_EXISTING, // Abre somente a porta existente
                       0, // Sem sobreposição de E/S
                       NULL); // Null para porta serial

    if (hComm == INVALID_HANDLE_VALUE) {
        printf("\n Erro! - Porta %s nao pode ser aberta\n", ComPortName);
        return 1; // Sai do programa em caso de erro
    } else {
        printf("\n Porta %s aberta\n", ComPortName);
    }

    /*--- Ajustando os parâmetros para a porta serial -----*/
    DCB dcbSerialParams = {0}; // Inicializando a estrutura DCB
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    Status = GetCommState(hComm, &dcbSerialParams); // Recebendo o estado corrente

    if (Status == FALSE) {
        printf("\n Erro em GetCommState()");
        CloseHandle(hComm);
        return 1; // Sai do programa em caso de erro
    }

    dcbSerialParams.BaudRate = CBR_115200; // Ajustando Baud Rate = 115200
    dcbSerialParams.ByteSize = 8; // Tamanho do byte = 8 dados
    dcbSerialParams.StopBits = ONESTOPBIT; // Ajustando stop bits = 1
    dcbSerialParams.Parity = NOPARITY; // Ajustando sem paridade

    Status = SetCommState(hComm, &dcbSerialParams); // Configurando a porta de acordo com os ajustes em DCB
    if (Status == FALSE) {
        printf("\n Erro em ajustar estrutura DCB");
        CloseHandle(hComm);
        return 1; // Sai do programa em caso de erro
    }

    /* The above code is a comment block in the C programming language. It is not performing any
    specific action or functionality in the program. Comments are used to provide explanations or
    notes within the code for better understanding by developers and are ignored by the compiler
    during the compilation process. */
    /*------ Ajustando timeouts --------------*/
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm, &timeouts) == FALSE) {
        printf("\n\n Erro em ajustar TimeOuts");
        CloseHandle(hComm);
        return 1; // Sai do programa em caso de erro
    }

    /*--------- Ajustando a máscara para receber -----------------*/
    Status = SetCommMask(hComm, EV_RXCHAR); // Configura Windows para monitorar a porta serial
    if (Status == FALSE) {
        printf("\n\n Erro! em ajustar CommMask");
        CloseHandle(hComm);
        return 1; // Sai do programa em caso de erro
    } else {
        printf("\n\n Aguardando recepcao de dados\n\n... ");
    }

    while (1) {
        /*------------ Ajustando evento WaitComm() -------*/
        Status = WaitCommEvent(hComm, &dwEventMask, NULL); // Aguarda por caractere

        /*-------- Programa aguarda aqui até o caractere ser recebido ------------*/
        if (Status == FALSE) {
            printf("\n Erro ao ajustar WaitCommEvent()");
        } else {
            i = 0;
            do {
                Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
                SerialBuffer[i++] = TempChar;
            } while (NoBytesRead > 0);

            /*------------ Imprime a string lida ----------------------*/
            printf("\n ");
            for (int j = 0; j < i; j++) { // j < i-1 para remover o último caractere duplicado
                printf("%c", SerialBuffer[j]);
            }

            // Respostas pré-definidas
            char pergunta1[] = "Qual a sua idade?";
            char pergunta2[] = "Onde voce nasceu?";
            char pergunta3[] = "Onde voce vive?";
            char pergunta4[] = "Tudo bem?";

            if (strncmp(pergunta1, SerialBuffer, strlen(pergunta1)) == 0) {
                strcpy(lpBuffer, "30 anos!\n\n");
            } else if (strncmp(pergunta2, SerialBuffer, strlen(pergunta2)) == 0) {
                strcpy(lpBuffer, "Em Sao Paulo\n\n");
            } else if (strncmp(pergunta3, SerialBuffer, strlen(pergunta3)) == 0) {
                strcpy(lpBuffer, "Em Vitoria - ES\n\n");
            } else if (strncmp(pergunta4, SerialBuffer, strlen(pergunta4)) == 0) {
                strcpy(lpBuffer, "Tudo bem. E você?\n\n");
            } else {
                strcpy(lpBuffer, "Nao entendi a pergunta.\n\n");
            }

            /*-------- Escrevendo caracteres para a porta serial -------------------*/
            DWORD dNoOFBytestoWrite = strlen(lpBuffer); // Número de bytes a escrever
            DWORD dNoOfBytesWritten = 0; // Número de bytes escritos

            Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
            if (Status == TRUE) {
                // printf("\n %s \n", lpBuffer); // Imprime dados escritos na porta
            } else {
                printf("\n\n Erro %d ao escrever na porta serial", GetLastError());
            }
        }
    }

    CloseHandle(hComm); // Fecha a porta serial
    printf("\n +=====================================+\n");
    return 0; // Sai do programa com sucesso
}
int serial(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s [list|read COMx|write COMx]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "list") == 0) {
        ListComPorts();
    } else if (strcmp(argv[1], "pergunta") == 0) {
        perguntaLeitura();
    } else if (strcmp(argv[1], "resposta") == 0) {
        pergunta();
    } else if (strcmp(argv[1], "test") == 0) {
        testOpen();
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