
#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

using namespace std;

volatile sig_atomic_t sigusr2Count = 0;

void sigusr1Handler(int signum) {
}

void sigusr2Handler(int signum) {
    ++sigusr2Count;
}

void sigintHandler(int signum) {
    cout << sigusr2Count << endl;
    exit(EXIT_SUCCESS);
}

int main() {
    signal(SIGUSR1, sigusr1Handler);

    signal(SIGUSR2, sigusr2Handler);

    signal(SIGINT, sigintHandler);

    while (true) {
        cout << "I am still alive!!" << endl;
        sleep(5);
    }

    return 0;
}
