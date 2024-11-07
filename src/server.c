#include <stdio.h>
#include <string.h>

#ifdef _WIN32
  // Windows-specific headers
  #include <winsock2.h>
  #include <ws2tcpip.h>  // for inet_pton, inet_ntop on Windows
  #pragma comment(lib, "ws2_32.lib")
#else
  // POSIX-specific headers
  #include <sys/types.h>
  #include <unistd.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
#endif
#define PORT 12345
#define BUFFER_SIZE 256

int tcpServerHTTP(int argc, char **argv) {
    int listenfd, connfd, size;
    struct sockaddr_in myaddr, cliaddr;

#ifdef _WIN32 
    WSADATA wsaData; 
    WSAStartup(MAKEWORD(2, 2), &wsaData); // Initialize Winsock 
#endif

    // Create socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Setup address structure
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(PORT);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(listenfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
        perror("Bind failed");
#ifdef _WIN32
        closesocket(listenfd);
#else
        close(listenfd);
#endif
#ifdef _WIN32
        WSACleanup(); // Cleanup Winsock
#endif
        return -1;
    }

    // Listen for incoming connections
    if (listen(listenfd, 3) < 0) {
        perror("Listen failed");
#ifdef _WIN32
        closesocket(listenfd);
#else
        close(listenfd);
#endif
#ifdef _WIN32
        WSACleanup(); // Cleanup Winsock
#endif
        return -1;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        printf("Waiting for connections...\n");
        memset(&cliaddr, 0, sizeof(cliaddr));
        size = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &size);
        if (connfd < 0) {
            perror("Accept failed");
            continue; // Continue to accept new connections
        }

        char buffer[BUFFER_SIZE];
        // Read the request
        int bytes_read = recv(connfd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the string
            printf("Received request:\n%s\n", buffer);
            
            // Prepare HTTP response
            const char *response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 13\r\n"
                "Connection: keep-alive\r\n"
                "Keep-Alive: timeout=5, max=100\r\n"
                "\r\n"
                "Hello, World!";

            // Send HTTP response
            send(connfd, response, strlen(response), 0);

            // Optionally, wait a bit before closing if `keep-alive` is desired
            Sleep(5000); // Wait for 5 seconds (1000 ms = 1 second)
        }
        // Close the connection
#ifdef _WIN32
        closesocket(connfd);
#else
        close(connfd);
#endif
        printf("Connection closed.\n");
    }

#ifdef _WIN32
    closesocket(listenfd);
    WSACleanup(); // Cleanup Winsock
#else
    close(listenfd);
#endif
    return 0;
}
int tcpServer(int argc, char **argv) {
    int listenfd, connfd, size;
    struct sockaddr_in myaddr, cliaddr;

#ifdef _WIN32 
    WSADATA wsaData; 
    WSAStartup(MAKEWORD(2, 2), &wsaData); // Initialize Winsock 
#endif

    // Create socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Setup address structure
    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(12345);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(listenfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
        perror("Bind failed");
#ifdef _WIN32
        closesocket(listenfd);
#else
        close(listenfd);
#endif
#ifdef _WIN32
        WSACleanup(); // Cleanup Winsock
#endif
        return -1;
    }

    // Listen for incoming connections
    if (listen(listenfd, 5) < 0) {
        perror("Listen failed");
#ifdef _WIN32
        closesocket(listenfd);
#else
        close(listenfd);
#endif
#ifdef _WIN32
        WSACleanup(); // Cleanup Winsock
#endif
        return -1;
    }

    printf("Server listening on port 12345...\n");

    // Accept incoming connections
    for (;;) {
        memset(&cliaddr, 0, sizeof(cliaddr));
        size = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &size);
        if (connfd < 0) {
            perror("Accept failed");
            continue; // Continue to accept new connections
        }

        // Send message to client
        const char *message = "Alo Mundo!";
        ssize_t sent_bytes = send(connfd, message, strlen(message), 0); // Use 0 instead of MSG_WAITALL

        if (sent_bytes < 0) {
            perror("Send failed");
        } else {
            printf("Sent %zd bytes to client: %s\n", sent_bytes, message);
        }

        // Close connection with client
#ifdef _WIN32
        closesocket(connfd);
#else
        close(connfd);
#endif
        printf("Connection closed.\n");
    }

#ifdef _WIN32
    closesocket(listenfd);
#else
    close(listenfd);
#endif

#ifdef _WIN32
    WSACleanup(); // Cleanup Winsock
#endif
    return 0;
}
int tcpClient(int argc, char **argv) {
    int sockfd;
    char recvline[20];
    struct sockaddr_in servaddr;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <IP address> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Creating socket...\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    
    // Convert IP address from text to binary
    if (inet_pton(AF_INET, argv[2], &servaddr.sin_addr) <= 0) {
        perror("Invalid address");
        closesocket(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connecting to server...\n");
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection failed");
        closesocket(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Waiting for message...\n");
    ssize_t recv_result = recv(sockfd, recvline, sizeof(recvline) - 1, 0);
    if (recv_result < 0) {
        perror("Receive failed");
    } else {
        recvline[recv_result] = '\0'; // Null-terminate the string
        printf("Received message: %s\n", recvline); // Print received message
    }

    closesocket(sockfd);
    return 0;
}
int udpServer() {
    int sockfd;
    char recvline[20];
    struct sockaddr_in myaddr, cliaddr;
    socklen_t addr_len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(12345);
    myaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
        perror("Bind failed");
        return -1;
    }

    for (;;) {
        // Receive message from client
        recvfrom(sockfd, recvline, sizeof(recvline) - 1, 0,
                 (struct sockaddr *)&cliaddr, &addr_len);
        recvline[sizeof(recvline) - 1] = '\0'; // Ensure null-termination

        // Send response back to client
        sendto(sockfd, "Alo Mundo!", strlen("Alo Mundo!"), 0,
               (struct sockaddr *)&cliaddr, addr_len);
    }

    closesocket(sockfd); // Cleanup
    return 0;
}
int udpClient(int argc, char **argv) {
    int sockfd;
    char sendline[] = "Hello, Server!";
    char recvline[20];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    
    if (inet_pton(AF_INET, argv[2], &servaddr.sin_addr) <= 0) {
        perror("Invalid address");
        closesocket(sockfd);
        return -1;
    }

    // Send message to server
    sendto(sockfd, sendline, strlen(sendline), 0,
           (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Receive response from server
    socklen_t addr_len = sizeof(servaddr);
    ssize_t recv_result = recvfrom(sockfd, recvline, sizeof(recvline) - 1, 0,
                                   (struct sockaddr *)&servaddr, &addr_len);
    if (recv_result < 0) {
        perror("Receive failed");
    } else {
        recvline[recv_result] = '\0'; // Null-terminate based on actual received length
        printf("Received message: %s\n", recvline);
    }

    closesocket(sockfd);
    return 0;
}

int server(int argc, char **argv) {
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
    if (strcmp(argv[1], "http-server") == 0) {
        tcpServerHTTP(argc, argv);
    } else if (strcmp(argv[1], "tcp-server") == 0) {
        tcpServer(argc, argv);
    } else if (strcmp(argv[1], "tcp-client") == 0) {
        tcpClient(argc, argv);
    } else if (strcmp(argv[1], "udp-server") == 0) {
        udpServer();
    } else if (strcmp(argv[1], "udp-client") == 0) {
        udpClient(argc, argv);
    } else {
        printf("Invalid argument.\n");
        return 1;
    }

    return 0;
}