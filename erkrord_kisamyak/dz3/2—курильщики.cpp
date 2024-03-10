#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t tobacco_sem;
sem_t paper_sem;
sem_t matches_sem;
sem_t bartender_sem;

void* smoker(void* arg) {
    char smoker_type = *((char*)arg);

    while (true) {
        sem_wait(&bartender_sem);

        switch (smoker_type) {
            case 't':
                std::cout << "Т получил табак и курит\n";
                break;
            case 'p':
                std::cout << "P получил бумагу и курит\n";
                break;
            case 'm':
                std::cout << "M получил спички и курит\n";
                break;
        }

        sleep(1);

        sem_post(&bartender_sem);

        pthread_exit(NULL);
    }

    return NULL;
}

void* bartender(void* arg) {
    char found_item;
    int num_smokers = 3;

    while (num_smokers > 0) {
        std::cin >> found_item;

        switch (found_item) {
            case 't':
                std::cout << "Бармен нашел табак\n";
                sem_post(&tobacco_sem);
                break;
            case 'p':
                std::cout << "Бармен нашел бумагу\n";
                sem_post(&paper_sem);
                break;
            case 'm':
                std::cout << "Бармен нашел спички\n";
                sem_post(&matches_sem);
                break;
            default:
                std::cerr << "Неизвестный предмет!\n";
                break;
        }

        sem_wait(&bartender_sem);

        num_smokers--;
    }

    return NULL;
}

int main() {
    sem_init(&tobacco_sem, 0, 0);
    sem_init(&paper_sem, 0, 0);
    sem_init(&matches_sem, 0, 0);
    sem_init(&bartender_sem, 0, 1);

    pthread_t smoker_threads[3];
    pthread_create(&smoker_threads[0], NULL, smoker, (void*) "t");
    pthread_create(&smoker_threads[1], NULL, smoker, (void*) "p");
    pthread_create(&smoker_threads[2], NULL, smoker, (void*) "m");

    pthread_t bartender_thread;
    pthread_create(&bartender_thread, NULL, bartender, NULL);

    pthread_join(bartender_thread, NULL);
    for (int i = 0; i < 3; ++i) {
        pthread_join(smoker_threads[i], NULL);
    }

    sem_destroy(&tobacco_sem);
    sem_destroy(&paper_sem);
    sem_destroy(&matches_sem);
    sem_destroy(&bartender_sem);

    return 0;
}
