#include <iostream>
#include <fstream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const std::string SERVER_ADDRESS = "www.ysu.am";
const int SERVER_PORT = 80;

int main() {
    std::string httpRequest = "GET / HTTP/1.1\r\nHost: " + SERVER_ADDRESS + "\r\n\r\n";

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error\n";
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_ADDRESS.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Error\n";
        return 1;
    }

    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "Error\n";
        return 1;
    }

    if (send(clientSocket, httpRequest.c_str(), httpRequest.size(), 0) == -1) {
        std::cerr << "Error\n";
        return 1;
    }
    std::string httpResponse;
    char buffer[1024];
    int bytesRead;
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        httpResponse.append(buffer, bytesRead);
    }

    std::cout << "Response:\n" << httpResponse << std::endl;

    std::ofstream outputFile("ysu.html");
    if (outputFile.is_open()) {
        outputFile << httpResponse;
        outputFile.close();
        std::cout << "Response saved to 'ysu.html'\n";
    } else {
        std::cerr << "Error\n";
    }

    close(clientSocket);

    return 0;
}
