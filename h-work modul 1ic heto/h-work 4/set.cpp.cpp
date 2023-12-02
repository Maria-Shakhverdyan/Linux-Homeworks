#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cmath>

int main() {
    const int size = 1000;
    const char* shm_name = "/my_shared_memory";
    int shm_fd = shm_open(shm_name, O_RDWR, 0666);
    
    int* arr = (int*)mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    for (int i = 2; i <= sqrt(size); ++i) {
        if (arr[i] == 0) {
            for (int j = i * i; j < size; j += i) {
                arr[j] = 1;
            }
        }
    }

    close(shm_fd);

    return 0;
}
