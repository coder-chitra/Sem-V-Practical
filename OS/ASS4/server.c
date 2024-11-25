#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    char *ip = "127.0.0.1";  // Correct IP address
    int port = 56007;
    int server_sock, client_sock, read_size;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char client_message[2000];
    char server_response[] = "Hello, this is from server.";  // Server response message

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("[-] Socket error");
        exit(1);
    }
    printf("[+] TCP server socket created\n");

    // Prepare the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    // Bind the socket
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-] Bind error");
        exit(1);
    }
    printf("[+] Bind to port %d\n", port);

    // Listen for incoming connections
    listen(server_sock, 5);
    printf("[+] Listening for incoming connections...\n");

    // Accept incoming client connections
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    if (client_sock < 0) {
        perror("[-] Accept failed");
        return 1;
    }
    printf("[+] Client connected\n");

    // Receive and send back a fixed server message
    while ((read_size = recv(client_sock, client_message, sizeof(client_message), 0)) > 0) {
        printf("Client: %s\n", client_message);
        send(client_sock, server_response, strlen(server_response), 0);  // Send server message
    }

    if (read_size == 0) {
        printf("Client disconnected\n");
    } else if (read_size == -1) {
        perror("[-] Recv failed");
    }

    // Close the socket
    close(server_sock);
    close(client_sock);
    return 0;
}
