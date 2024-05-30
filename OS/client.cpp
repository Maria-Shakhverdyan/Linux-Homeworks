#include "Bank.h"
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <sstream>

int main() {
    int shm_fd = shm_open("/bank_shm", O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to open shared memory\n";
        return 1;
    }

    size_t size = sizeof(Bank);
    if (ftruncate(shm_fd, size) == -1) {
        std::cerr << "Failed to set size of shared memory\n";
        return 1;
    }

    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        std::cerr << "Failed to map shared memory\n";
        return 1;
    }

    Bank* bank = static_cast<Bank*>(ptr);

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "freeze") {
            int account;
            iss >> account;
            bank->freezeAccount(account);
        } else if (command == "unfreeze") {
            int account;
            iss >> account;
            bank->unfreezeAccount(account);
        } else if (command == "transfer") {
            int from, to, amount;
            iss >> from >> to >> amount;
            bank->transfer(from, to, amount);
        } else if (command == "update_all") {
            int amount;
            iss >> amount;
            bank->updateAllBalances(amount);
        } else if (command == "set_min") {
            int account, min_balance;
            iss >> account >> min_balance;
            bank->setMinBalance(account, min_balance);
        } else if (command == "set_max") {
            int account, max_balance;
            iss >> account >> max_balance;
            bank->setMaxBalance(account, max_balance);
        } else if (command == "get_current") {
            int account;
            iss >> account;
            int balance = bank->getCurrentBalance(account);
            if (balance != -1) {
                std::cout << "Current balance of account " << account << " is " << balance << "\n";
            }
        } else if (command == "get_min") {
            int account;
            iss >> account;
            int balance = bank->getMinBalance(account);
            if (balance != -1) {
                std::cout << "Minimum balance of account " << account << " is " << balance << "\n";
            }
        } else if (command == "get_max") {
            int account;
            iss >> account;
            int balance = bank->getMaxBalance(account);
            if (balance != -1) {
                std::cout << "Maximum balance of account " << account << " is " << balance << "\n";
            }
        } else {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}

