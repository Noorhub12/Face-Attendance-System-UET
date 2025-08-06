#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <direct.h>  // For creating directories

#define PORT 8080
#define BUFFER_SIZE 1024
#define SAVE_FOLDER "D:\\5th Semester\\spprroject\\Face_recognition_based_attendance_system\\Recieved_Files\\"

void error_exit(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_len;
    char buffer[BUFFER_SIZE];
    char file_name[256];
    
    // Initialize Winsock
    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        error_exit("WSAStartup failed");
    }

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        error_exit("Socket creation failed");
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.43.126");  // Specify server's IP address (replace with actual IP)
    server.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        error_exit("Bind failed");
    }

    // Listen for connections
    listen(server_socket, 3);
    printf("Server is listening on port %d...\n", PORT);

    // Accept incoming connection
    client_len = sizeof(client);
    client_socket = accept(server_socket, (struct sockaddr*)&client, &client_len);
    if (client_socket == INVALID_SOCKET) {
        error_exit("Accept failed");
    }

    printf("Client connected!\n");

    // Receive the filename
    int bytes_received = recv(client_socket, file_name, sizeof(file_name), 0);
    if (bytes_received <= 0) {
        error_exit("Failed to receive file name");
    }
    file_name[bytes_received - 1] = '\0';  // Remove newline character

    // Construct full path
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s%s", SAVE_FOLDER, file_name);

    // Open file for writing
    FILE *file = fopen(full_path, "wb");
    if (file == NULL) {
        error_exit("Failed to open file for writing");
    }

    // Receive file data
    printf("Receiving file: %s...\n", file_name);
    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, file);
    }
    
    printf("File received and saved at: %s\n", full_path);

    // Cleanup
    fclose(file);
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
