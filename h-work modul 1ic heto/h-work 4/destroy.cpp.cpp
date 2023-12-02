#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    const char* shm_name = "/my_shared_memory";
    int shm_fd = shm_open(shm_name, O_RDWR, 0666);

    shm_unlink(shm_name);

    return 0;
}
