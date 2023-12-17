#include <iostream>
#include <vector>
#include <pthread.h>

class Number {
public:
    int x = 0;
};

class Semaphore {
public:
    explicit Semaphore(int count) : count_(count) {
        pthread_mutex_init(&mutex_, nullptr);
        pthread_cond_init(&condition_, nullptr);
    }

    ~Semaphore() {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&condition_);
    }

    void wait() {
        pthread_mutex_lock(&mutex_);
        while (count_ <= 0) {
            pthread_cond_wait(&condition_, &mutex_);
        }
        count_--;
        pthread_mutex_unlock(&mutex_);
    }

    void signal() {
        pthread_mutex_lock(&mutex_);
        count_++;
        pthread_cond_signal(&condition_);
        pthread_mutex_unlock(&mutex_);
    }

private:
    int count_;
    pthread_mutex_t mutex_;
    pthread_cond_t condition_;
};

Semaphore semaphore(1);

void* example(void* arg) {
    Number* num = static_cast<Number*>(arg);
    for (int i = 0; i < 10000; ++i) {
        semaphore.wait();
        num->x++;
        semaphore.signal();
    }
    return nullptr;
}

int main(int argc, char** argv) {
    Number* num = new Number();
    num->x = 2;
    std::vector<pthread_t> tids(20);

    for (int i = 0; i < 20; ++i) {
        pthread_create(&tids[i], nullptr, example, num);  
    }

    for (int i = 0; i < 20; ++i) {
        pthread_join(tids[i], nullptr);
    }

    std::cout << num->x << std::endl;
    delete num;

    return 0;
}
