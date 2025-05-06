#include <iostream>
#include <unistd.h>     // fork
#include <sys/mman.h>   // mmap
#include <semaphore.h>  // sem_t, sem_init, etc.
#include <sys/wait.h>   // wait
#include "factorial.h"  // factorial function

int main() {
    // Create shared memory for the result
    int* result = static_cast<int*>(mmap(nullptr, sizeof(int),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    if (result == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Create a semaphore in shared memory
    sem_t* sem = static_cast<sem_t*>(mmap(nullptr, sizeof(sem_t),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    if (sem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    sem_init(sem, 1, 0); // 1 - for interprocess use, 0 - initial value

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process: calculates factorial and writes to shared memory
        *result = factorial(5);

        // We signal that the result is ready
        sem_post(sem);

        // Exiting a child process
        return 0;
    }
    else {
        // Parent process: waiting for signal from semaphore
        sem_wait(sem);

        // Reads the result
        std::cout << "Factorial calculated in child process: " << *result << std::endl;

        // Waits for the child process to complete
        wait(nullptr);

        // Resource Cleanup
        sem_destroy(sem);
        munmap(result, sizeof(int));
        munmap(sem, sizeof(sem_t));

        return 0;
    }
}