#include <iostream>
#include <vector>
#include <pthread.h>

class Number {
public:
    int x = 0;
};

class Mutex {
public:
    Mutex() {
        pthread_mutex_init(&mutex_, nullptr);
    }

    ~Mutex() {
        pthread_mutex_destroy(&mutex_);
    }

    void lock() {
        pthread_mutex_lock(&mutex_);
    }

    void unlock() {
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
};

Mutex mutex;

void* example(void* arg) {
    Number* num = static_cast<Number*>(arg);
    for (int i = 0; i < 10000; ++i) {
        mutex.lock();
        num->x++;
        mutex.unlock();
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
