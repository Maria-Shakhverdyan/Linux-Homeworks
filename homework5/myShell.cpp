#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::string vvod;

    while (true) {
        std::cout << "myShell> ";
        std::getline(std::cin, vvod);

        if (vvod == "exit") {
            break;
        }

        pid_t pid = fork();

        if (pid == -1) {
            std::cerr << "Error" << std::endl;
            return 1;
        }

        if (pid == 0) {
            execlp(vvod.c_str(), vvod.c_str(), nullptr);
            std::cerr << "Error." << std::endl;
            return 1;
        } else {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                std::cout << "exit code: " << WEXITSTATUS(status) << std::endl;
            }
        }
    }

    return 0;
}
