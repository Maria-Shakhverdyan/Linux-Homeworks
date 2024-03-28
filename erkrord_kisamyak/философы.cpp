#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cerrno>
#include <vector>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <cstdlib>

const int NUM_PHILOSOPHERS = 5;
const char* SEM_NAME = "/dining_philosophers";

std::vector<sem_t*> sems(NUM_PHILOSOPHERS);
std::vector<pid_t> pids(NUM_PHILOSOPHERS);

void philosoph(std::size_t philNum)
{
    int leftFork = philNum;
    int rightFork = (philNum + 1) % NUM_PHILOSOPHERS;
    std::string eating = std::to_string(philNum) + ": I am eating\n";
    std::string thinking = std::to_string(philNum) + ": I am thinking\n";
    sem_wait(sems[leftFork]);
    sem_wait(sems[rightFork]);
    std::cout << eating;
    sleep(3);
    std::cout << thinking;
    sem_post(sems[rightFork]);
    sem_post(sems[leftFork]);
}

int main()
{
    sem_unlink(SEM_NAME);
    for(std::size_t j = 0; j < NUM_PHILOSOPHERS; ++j)
    {
        sems[j] = sem_open(SEM_NAME, O_CREAT, 0644, 1);
        if (sems[j] == SEM_FAILED) {
            perror("sem_open");
            exit(EXIT_FAILURE);
        }
    }

    for(std::size_t i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        pids[i] = fork();
        if(pids[i] == 0)
        {
            philosoph(i);
            exit(0);
        }
    }

    for(std::size_t i = 0; i < pids.size(); ++i)
    {
        if(waitpid(pids[i], nullptr, 0) == -1)
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }

    for (std::size_t i = 0; i < sems.size(); ++i) {
        sem_close(sems[i]);
    }
    sem_unlink(SEM_NAME);

    return 0;
}
