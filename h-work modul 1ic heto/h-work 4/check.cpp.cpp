#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr<< argv[0] << " Check" << std::endl;
        return 1;
    }

    int numberToCheck = std::stoi(argv[1]);
    const char* shm_name = "/my_shared_memory";

    int shm_fd = shm_open(shm_name, O_RDWR, 0666);
    
    int* arr = (int*)mmap(NULL, 1000 * sizeof(int), PROT_READ, MAP_SHARED, shm_fd, 0);

    if (numberToCheck >= 0 && numberToCheck < 1000 && arr[numberToCheck] == 0) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    close(shm_fd);

    return 0;
}
