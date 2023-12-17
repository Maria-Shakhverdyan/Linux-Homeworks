#include <iostream>
#include <vector>
#include <pthread.h>

class Number {
public:
    int x = 0;
};

volatile bool spinlock = false;

void* example(void* arg) {
    Number* num = static_cast<Number*>(arg);
    for (int i = 0; i < 10000; ++i) {
        while (__sync_lock_test_and_set(&spinlock, true));
        num->x++;
        __sync_lock_release(&spinlock);
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
