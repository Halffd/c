#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#define SOCKET_ERROR_CODE WSAGetLastError()
#define CLOSE_SOCKET(sock) closesocket(sock)
#define INITIALIZE_WINSOCK() WSAStartup(MAKEWORD(2, 2), &wsaData)
#define SHUTDOWN_WINSOCK() WSACleanup()
DWORD WINAPI clientHandler(void* clientData);
DWORD WINAPI receiveMessages(void* socket_desc);
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR_CODE errno
#define CLOSE_SOCKET(sock) close(sock)
#define INITIALIZE_WINSOCK() // No operation for POSIX
#define SHUTDOWN_WINSOCK() // No operation for POSIX
#endif

#define PORT 12345
#define MAX_CLIENTS 10
#define BUFFER_SIZE 256

typedef struct {
    SOCKET socket;
    char username[30];
} Client;

Client clients[MAX_CLIENTS];
int clientCount = 0;

void broadcastMessage(const char* message, SOCKET senderSocket);
void* clientHandlerPOSIX(void* clientData);
void* receiveMessagesPOSIX(void* socket_desc);

// Server code
int chatServer() {
#ifdef _WIN32
    WSADATA wsaData;
    INITIALIZE_WINSOCK();
#endif

    SOCKET serverSocket, newSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(struct sockaddr_in);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        fprintf(stderr, "Could not create socket. Error Code: %d\n", SOCKET_ERROR_CODE);
        return 1;
    }

    // Prepare the sockaddr_in structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        fprintf(stderr, "Bind failed. Error Code: %d\n", SOCKET_ERROR_CODE);
        return 1;
    }

    // Listen
    listen(serverSocket, 3);
    printf("Server listening on port %d...\n", PORT);

    // Accept incoming connections
    while (clientCount < MAX_CLIENTS) {
        newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (newSocket == INVALID_SOCKET) {
            fprintf(stderr, "Accept failed. Error Code: %d\n", SOCKET_ERROR_CODE);
            return 1;
        }

        // Get username
        char username[30];
        recv(newSocket, username, sizeof(username), 0);
        strcpy(clients[clientCount].username, username);
        clients[clientCount].socket = newSocket;
        clientCount++;

        printf("Client connected: %s (%d)\n", username, newSocket);

        // Welcome message
        char welcomeMessage[BUFFER_SIZE];
        snprintf(welcomeMessage, sizeof(welcomeMessage), "%s has joined the chat.\n", username);
        broadcastMessage(welcomeMessage, newSocket);

        // Create a thread for each client
#ifdef _WIN32
        CreateThread(NULL, 0, clientHandler, (void*)&clients[clientCount - 1], 0, NULL);
#else
        pthread_t thread;
        pthread_create(&thread, NULL, clientHandlerPOSIX, (void*)&clients[clientCount - 1]);
#endif
    }

    CLOSE_SOCKET(serverSocket);
    SHUTDOWN_WINSOCK();
    return 0;
}

#ifdef _WIN32
DWORD WINAPI clientHandler(void* clientData) {
#else
void* clientHandlerPOSIX(void* clientData) {
#endif
    Client* client = (Client*)clientData;
    char buffer[BUFFER_SIZE];
    int recvSize;

    while ((recvSize = recv(client->socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[recvSize] = '\0'; // Null-terminate the string
        broadcastMessage(buffer, client->socket);
    }

    CLOSE_SOCKET(client->socket);
    printf("Client disconnected: %s (%d)\n", client->username, client->socket);
#ifdef _WIN32
    return 0;
#else
    return NULL;
#endif
}

void broadcastMessage(const char* message, SOCKET senderSocket) {
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].socket != senderSocket) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
}

// Client code
int chatClient() {
#ifdef _WIN32
    WSADATA wsaData;
    INITIALIZE_WINSOCK();
#endif

    SOCKET sock;
    struct sockaddr_in serverAddr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "Could not create socket. Error Code: %d\n", SOCKET_ERROR_CODE);
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        fprintf(stderr, "Connect failed. Error Code: %d\n", SOCKET_ERROR_CODE);
        return 1;
    }

    char username[30];
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character
    send(sock, username, sizeof(username), 0);

    printf("Connected to server. You can start chatting!\n");

#ifdef _WIN32
    CreateThread(NULL, 0, receiveMessages, (void*)&sock, 0, NULL);
#else
    pthread_t thread;
    pthread_create(&thread, NULL, receiveMessagesPOSIX, (void*)&sock);
#endif

    char buffer[BUFFER_SIZE];
    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);
    }

    CLOSE_SOCKET(sock);
    SHUTDOWN_WINSOCK();
    return 0;
}

#ifdef _WIN32
DWORD WINAPI receiveMessages(void* socket_desc) {
#else
void* receiveMessagesPOSIX(void* socket_desc) {
#endif
    SOCKET sock = *(SOCKET*)socket_desc;
    char buffer[BUFFER_SIZE];
    int recvSize;

    while ((recvSize = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[recvSize] = '\0';
        printf("Received: %s", buffer);
    }

    printf("Disconnected from server.\n");
    CLOSE_SOCKET(sock);
#ifdef _WIN32
    return 0;
#else
    return NULL;
#endif
}

// Main function
int chat(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s [server|client]\n", argv[0]);
        return 1;
    }

#ifdef _WIN32
    INITIALIZE_WINSOCK();
#endif

    if (strcmp(argv[1], "client") == 0) {
        chatClient();
    } else if (strcmp(argv[1], "server") == 0) {
        chatServer();
    } else {
        printf("Invalid argument. Use 'server' or 'client'.\n");
        return 1;
    }

    SHUTDOWN_WINSOCK();
    return 0;
}