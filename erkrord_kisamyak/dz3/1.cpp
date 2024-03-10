#include <iostream>
#include <pthread.h>
#include <vector>
#include <queue>

const int SIZE = 8;

pthread_mutex_t mutex;
pthread_cond_t empty;
pthread_cond_t full;
std::queue<char> buffer;
bool bufferFull = false;
bool bufferEmpty = true;

void* produce(void* arg)
{
    char c = *((char*)arg);
    for(int i = 0; i < 2; ++i)
    {
        pthread_mutex_lock(&mutex);
        while (bufferFull)
            pthread_cond_wait(&empty, &mutex);

        buffer.push(c);
        std::cout << "produced: " << c << std::endl;

        if (buffer.size() == SIZE)
            bufferFull = true;
        
        bufferEmpty = false;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

void* consume(void* arg)
{
    for(int i = 0; i < 2; ++i)
    {
        pthread_mutex_lock(&mutex);
        while (bufferEmpty)
            pthread_cond_wait(&full, &mutex);

        char c = buffer.front();
        buffer.pop();
        std::cout << "consumed: " << c << std::endl;

        if (buffer.size() == 0)
            bufferEmpty = true;
        
        bufferFull = false;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

int main()
{
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&empty, nullptr);
    pthread_cond_init(&full, nullptr);

    std::vector<pthread_t> threads(20);
    std::vector<char> data{'a','b','c','d','e','f','g','h','i','j'};
    for(int i = 0; i < 20; i+=2)
    {
        pthread_create(&threads[i], nullptr, produce, &data[i/2]);
        pthread_create(&threads[i+1], nullptr, consume, &data[i/2]);
    }

    for(int i = 0; i < 20; ++i)
    {
        pthread_join(threads[i], nullptr); 
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    return 0;
}
