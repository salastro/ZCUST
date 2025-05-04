#pragma once
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_KEY 0x1234

// Shared resources
int *buffer;
int buffer_size;
sem_t *space, *items, *mutex;
int shm_id; // Shared memory ID

// Function prototypes
void memory_init();
void memory_cleanup();

// Initialize shared memory and semaphores
void memory_init() {
  // Allocate shared memory
  shm_id = shmget(SHM_KEY, buffer_size * sizeof(int), IPC_CREAT | 0666);
  if (shm_id == -1) {
    perror("shmget");
    exit(EXIT_FAILURE);
  }

  // Attach shared memory to buffer
  buffer = (int *)shmat(shm_id, NULL, 0);
  if (buffer == (void *)-1) {
    perror("shmat");
    exit(EXIT_FAILURE);
  }

  // Initialize semaphores
  space = sem_open("space", O_CREAT, 0666, buffer_size);
  items = sem_open("items", O_CREAT, 0666, 0);
  mutex = sem_open("mutex", O_CREAT, 0666, 1);
  if (space == SEM_FAILED || items == SEM_FAILED || mutex == SEM_FAILED) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
}

// Cleanup shared memory and semaphores
void memory_cleanup() {
  // Detach the shared memory
  if (shmdt(buffer) == -1) {
    perror("shmdt");
  }

  // Destroy semaphores
  if (sem_close(space) == -1 || sem_close(items) == -1 || sem_close(mutex) == -1) {
    perror("sem_close");
  }

  // Remove shared memory segment
  if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
    perror("shmctl");
  }

  // Unlink semaphores
  if (sem_unlink("space") == -1 || sem_unlink("items") == -1 || sem_unlink("mutex") == -1) {
    perror("sem_unlink");
  }
}
