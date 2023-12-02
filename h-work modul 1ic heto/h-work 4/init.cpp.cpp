#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    const int size = 1000;
    const char* shm_key = "/my_shared_memory";

    key_t key = ftok(shm_key, 'R');
    int shmid = shmget(key, size * sizeof(int), IPC_CREAT | 0666);

    int *arr = (int *)shmat(shmid, NULL, 0);

    memset(arr, 0, size * sizeof(int));
    shmdt(arr);

    return 0;
}
