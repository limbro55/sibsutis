#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    sockaddr_in server_addr{}, client_addr{};
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = 0; 

    
    if (bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        return EXIT_FAILURE;
    }

    // узнать порт
    socklen_t len = sizeof(server_addr);
    if (getsockname(sockfd, (sockaddr*)&server_addr, &len) == -1) {
        perror("getsockname failed");
        close(sockfd);
        return EXIT_FAILURE;
    }

    std::cout << "Server started on port: "
              << ntohs(server_addr.sin_port) << std::endl;

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);

        ssize_t recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                    (sockaddr*)&client_addr, &client_len);

        if (recv_len < 0) {
            perror("recvfrom failed");
            continue;
        }

        int number = std::atoi(buffer);

        std::cout << "Received from "
                  << inet_ntoa(client_addr.sin_addr)
                  << ":" << ntohs(client_addr.sin_port)
                  << " -> " << number << std::endl;

        
        int transformed = number;
        std::snprintf(buffer, BUFFER_SIZE, "%d", transformed);

        sendto(sockfd, buffer, std::strlen(buffer), 0,
               (sockaddr*)&client_addr, client_len);
    }

    close(sockfd);
    return 0;
}