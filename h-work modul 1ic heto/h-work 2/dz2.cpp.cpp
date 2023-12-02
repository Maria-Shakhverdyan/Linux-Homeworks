
#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        cerr << "Error" << endl;
        return EXIT_FAILURE;
    } else if (pid == 0) {
        sleep(2);

        if (kill(getppid(), SIGKILL) == -1) {
            cerr << "Vsyo ploxo" << endl;
        } else {
            cout << "Vsyo xorosho" << endl;
        }

        cout << "Sharunakvuma" << endl;
        sleep(5);
        cout << "Verjacav" << endl;
    } else {
        cout << "PID = " << getpid() << endl;

        setpgrp();
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            cout << WEXITSTATUS(status) << endl;
        } else {
            cerr << "Error" << endl;
        }

        cout << "Verjacav" << endl;
    }

    return 0;
}
