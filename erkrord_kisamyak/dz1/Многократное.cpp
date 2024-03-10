#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error\n";
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "Error\n";
        return 1;
    }

    std::string message;
    do {
        std::cout << "Enter message ";
        std::getline(std::cin, message);

        if (send(clientSocket, message.c_str(), message.size(), 0) == -1) {
            std::cerr << "Error\n";
            break;
        }
    } while (message != "quit");

    close(clientSocket);
    return 0;
}
