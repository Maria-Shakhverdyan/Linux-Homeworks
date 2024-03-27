#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int tobacco_pipe[2];
int paper_pipe[2];
int matches_pipe[2];

void smoker(const char smoker_type) {
    char buf;
    while (true) {
        read(tobacco_pipe[0], &buf, sizeof(buf));

        if (buf == smoker_type) {
            switch (smoker_type) {
                case 't':
                    std::cout << "T got tobacco and smokes\n";
                    break;
                case 'p':
                    std::cout << "P got the paper and smokes\n";
                    break;
                case 'm':
                    std::cout << "M got matches and smokes\n";
                    break;
            }
            sleep(1);
            write(tobacco_pipe[1], &buf, sizeof(buf));
        }
    }
}

void bartender() {
    char found;
    int smokers_count = 3;

    while (smokers_count > 0) {
        std::cin >> found;

        switch (found) {
            case 't':
                std::cout << "The bartender found tobacco\n";
                write(tobacco_pipe[1], &found, sizeof(found));
                break;
            case 'p':
                std::cout << "The bartender found the paper\n";
                write(paper_pipe[1], &found, sizeof(found));
                break;
            case 'm':
                std::cout << "The bartender found matches\n";
                write(matches_pipe[1], &found, sizeof(found));
                break;
            default:
                std::cerr << "Unknown item!\n";
                break;
        }

        smokers_count--;
    }
}

int main() {
    pipe(tobacco_pipe);
    pipe(paper_pipe);
    pipe(matches_pipe);

    if (fork() == 0) {
        smoker('t');
    }

    if (fork() == 0) {
        smoker('p');
    }

    if (fork() == 0) {
        smoker('m');
    }

    bartender();

    close(tobacco_pipe[0]);
    close(tobacco_pipe[1]);
    close(paper_pipe[0]);
    close(paper_pipe[1]);
    close(matches_pipe[0]);
    close(matches_pipe[1]);

    while (wait(NULL) != -1);

    return 0;
}
