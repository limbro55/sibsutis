#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0]
                  << " <server_ip> <port> <N>" << std::endl;
        return EXIT_FAILURE;
    }

    const char* server_ip = argv[1];
    int port = std::atoi(argv[2]);
    int N = std::atoi(argv[3]);

    int sockfd;
    sockaddr_in server_addr{};
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        close(sockfd);
        return EXIT_FAILURE;
    }

    while (true) {
        std::snprintf(buffer, BUFFER_SIZE, "%d", N);

        sendto(sockfd, buffer, std::strlen(buffer), 0,
               (sockaddr*)&server_addr, sizeof(server_addr));

        memset(buffer, 0, BUFFER_SIZE);

        ssize_t recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, nullptr, nullptr);

        if (recv_len > 0) {
            std::cout << "Server response: " << buffer << std::endl;
        }

        sleep(N);
    }

    close(sockfd);
    return 0;
}