#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    char *ip = "127.0.0.1";  // Correct IP address
    int port = 56007;
    int sock;
    struct sockaddr_in addr;
    char buffer[1024];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-] Socket error");
        exit(1);
    }
    printf("[+] TCP client socket created.\n");

    // Set up server address
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("[-] Connection error");
        exit(1);
    }
    printf("[+] Connected to server.\n");

    // Send message to server
    strcpy(buffer, "HELLO, THIS IS CLIENT.");
    printf("Client: %s\n", buffer);
    send(sock, buffer, strlen(buffer), 0);

    // Receive response from server
    bzero(buffer, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);  // The server's response

    // Close the socket
    close(sock);
    printf("[+] Disconnected from server.\n");

    return 0;
}
