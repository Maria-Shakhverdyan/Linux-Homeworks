
#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << argv[0] << endl;
        return EXIT_FAILURE;
    }

    int signalNumber = atoi(argv[1]);
    pid_t pid = atoi(argv[2]);

    if (kill(pid, signalNumber) == -1) {
        cerr << "Error" << endl;
        return EXIT_FAILURE;
    }

    cout << signalNumber << pid << endl;

    return EXIT_SUCCESS;
}
