
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t child1 = fork();

    if (child1 == -1) {
        perror("fork");
        return 1;
    }

    if (child1 == 0) {

        close(pipefd[0]);

        pid_t mypid = getpid();

        write(pipefd[1], &mypid, sizeof(mypid));

        close(pipefd[1]);

        std::cout << mypid << std::endl;

        return 0;
    } else {
        pid_t child2 = fork();

        if (child2 == -1) {
            perror("fork");
            return 1;
        }

        if (child2 == 0) {
            close(pipefd[1]);

            pid_t mypid = getpid();

            pid_t pid_from_child1;
            read(pipefd[0], &pid_from_child1, sizeof(pid_from_child1));

            close(pipefd[0]);

            std::cout << mypid << std::endl;
            std::cout << pid_from_child1 << std::endl;

            return 0;
        } else {

            close(pipefd[0]);
            close(pipefd[1]);

            waitpid(child1, nullptr, 0);
            waitpid(child2, nullptr, 0);
        }
    }

    return 0;
}
