#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

std::mutex consoleMutex;

void handleClient(int clientSocket) {
    char buffer[1024];
    int bytesRead;
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesRead] = '\0';
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::cout << "Message from client: " << buffer << std::endl;
    }
    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error\n";
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "Error\n";
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == -1) {
        std::cerr << "Error\n";
        return 1;
    }

    std::vector<std::thread> clientThreads;

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);
        if (clientSocket == -1) {
            std::cerr << "Error\n";
            continue;
        }

        clientThreads.emplace_back(handleClient, clientSocket);
    }

    for (auto& thread : clientThreads) {
        thread.join();
    }

    return 0;
}
