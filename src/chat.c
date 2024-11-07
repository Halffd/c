#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>

#define PORT 12345
#define MAX_CLIENTS 10
#define BUFFER_SIZE 256

typedef struct {
    SOCKET socket;
    char username[30];
} Client;

Client clients[MAX_CLIENTS];
int clientCount = 0;

DWORD WINAPI clientHandler(void* clientData);

void broadcastMessage(const char* message, SOCKET senderSocket) {
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].socket != senderSocket) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
}

int chatServer() {
    WSADATA wsaData;
    SOCKET serverSocket, newSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(struct sockaddr_in);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        fprintf(stderr, "Could not create socket. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Prepare the sockaddr_in structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        fprintf(stderr, "Bind failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Listen
    listen(serverSocket, 3);
    printf("Server listening on port %d...\n", PORT);

    // Accept and incoming connection
    for (int i = 0; i < MAX_CLIENTS; i++) {
        newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (newSocket == INVALID_SOCKET) {
            fprintf(stderr, "Accept failed. Error Code: %d\n", WSAGetLastError());
            return 1;
        }

        // Get username
        char username[30];
        recv(newSocket, username, sizeof(username), 0);
        strcpy(clients[clientCount].username, username);
        clients[clientCount].socket = newSocket;
        clientCount++;

        printf("Client connected: %s (%d)\n", username, newSocket);

        // Send welcome message
        char welcomeMessage[BUFFER_SIZE];
        snprintf(welcomeMessage, sizeof(welcomeMessage), "%s has joined the chat.\n", username);
        broadcastMessage(welcomeMessage, newSocket);

        // Create a thread for each client
        CreateThread(NULL, 0, clientHandler, (void*)&clients[clientCount - 1], 0, NULL);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}

DWORD WINAPI clientHandler(void* clientData) {
    Client* client = (Client*)clientData;
    char buffer[BUFFER_SIZE];
    int recvSize;

    // Receive messages from client
    while ((recvSize = recv(client->socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[recvSize] = '\0'; // Null-terminate the string

        // Get the current time
        time_t now = time(NULL);
        struct tm* local = localtime(&now);
        char timeStamp[30];
        strftime(timeStamp, sizeof(timeStamp), "[%Y-%m-%d %H:%M:%S] ", local);

        // Prepare the message
        char message[BUFFER_SIZE + 30];
        snprintf(message, sizeof(message), "%s%s: %s", timeStamp, client->username, buffer);

        printf("Message from %s: %s", client->username, buffer);

        // Send the message to all other clients
        broadcastMessage(message, client->socket);
    }

    // Client disconnected
    closesocket(client->socket);
    printf("Client disconnected: %s (%d)\n", client->username, client->socket);

    // Notify other clients
    char leaveMessage[BUFFER_SIZE];
    snprintf(leaveMessage, sizeof(leaveMessage), "%s has left the chat.\n", client->username);
    broadcastMessage(leaveMessage, client->socket);

    return 0;
}
#define PORT 12345
#define BUFFER_SIZE 256

DWORD WINAPI receiveMessages(void* socket_desc);

int chatClient() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serverAddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "Could not create socket. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Prepare the sockaddr_in structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change this to server IP if needed
    serverAddr.sin_port = htons(PORT);

    // Connect to remote server
    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        fprintf(stderr, "Connect failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Input username
    char username[30];
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    // Send username to server
    send(sock, username, sizeof(username), 0);

    printf("Connected to server. You can start chatting!\n");

    // Create a thread to receive messages
    CreateThread(NULL, 0, receiveMessages, (void*)&sock, 0, NULL);

    // Main loop to send messages
    char buffer[BUFFER_SIZE];
    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin); // Read input from user
        send(sock, buffer, strlen(buffer), 0); // Send message to server
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}

DWORD WINAPI receiveMessages(void* socket_desc) {
    SOCKET sock = *(SOCKET*)socket_desc;
    char buffer[BUFFER_SIZE];
    int recvSize;

    // Receive messages from server
    while ((recvSize = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[recvSize] = '\0'; // Null-terminate the string
        printf("Received: %s", buffer);
    }

    printf("Disconnected from server.\n");
    closesocket(sock);
    return 0;
}

int chat(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return -1;
    }
    #endif
    if (strcmp(argv[1], "client") == 0) {
        chatClient(argc, argv);
    } else if (strcmp(argv[1], "server") == 0) {
        chatServer();
    } else {
        printf("Invalid argument.\n");
        return 1;
    }

    return 0;
}
