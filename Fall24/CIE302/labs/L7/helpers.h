#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define SHM_KEY 1234
#define MAX_MSG_SIZE 256
#define SEM_CON_NAME "/sem_con"
#define SEM_PRO_NAME "/sem_pro"
#define SEM_LOCK_NAME "/sem_lock"

// Shared memory pointer
int shm_id;
char *shared_memory;

// POSIX semaphores
sem_t *sem_con; // Semaphore for consumers
sem_t *sem_pro; // Semaphore for producers
sem_t *sem_lock; // Mutex for critical sections

// Function prototypes
char *generate_shm();
int destroy_shm();
sem_t *open_semaphore(const char *name, unsigned int value);
int destroy_semaphores();

// Function definitions
//

// Create shared memory
char *generate_shm() {
    shm_id = shmget(SHM_KEY, MAX_MSG_SIZE * 2, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }
    char *shared_memory = (char *)shmat(shm_id, NULL, 0);
    if ((intptr_t)shared_memory == -1) {
        perror("shmat failed");
        exit(1);
    }
    return shared_memory;
}

// Destroy shared memory
int destroy_shm() {
    int ret = shmctl(shm_id, IPC_RMID, NULL);
    if (ret == -1)
        perror("shmctl failed");
    return ret;
}

// Create or open a semaphore
sem_t *open_semaphore(const char *name, unsigned int value) {
    sem_t *sem = sem_open(name, O_CREAT, 0666, value);
    if (sem == SEM_FAILED) {
        perror("sem_open failed");
        exit(1);
    }
    return sem;
}

// Destroy semaphores
int destroy_semaphores() {
    if (sem_unlink(SEM_CON_NAME) == -1)
        perror("sem_unlink (consumer) failed");
    if (sem_unlink(SEM_PRO_NAME) == -1)
        perror("sem_unlink (producer) failed");
    if (sem_unlink(SEM_LOCK_NAME) == -1)
        perror("sem_unlink (lock) failed");
    return 0;
}
