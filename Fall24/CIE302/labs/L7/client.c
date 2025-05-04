#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_message(char *message, size_t max_size);

int main() {
    // Attach to shared memory and semaphores
    shared_memory = generate_shm();
    sem_con = open_semaphore(SEM_CON_NAME, 0);
    sem_pro = open_semaphore(SEM_PRO_NAME, 0);
    sem_lock = open_semaphore(SEM_LOCK_NAME, 1);

    while (1) {
        char message[MAX_MSG_SIZE];
        get_message(message, MAX_MSG_SIZE);

        // Lock shared memory
        sem_wait(sem_lock);

        // Write to shared memory
        strcpy(shared_memory, message);

        // Unlock shared memory
        sem_post(sem_lock);

        // Notify server
        sem_post(sem_pro);

        // Wait for server to process
        sem_wait(sem_con);

        // Read response
        if (strlen(shared_memory) > 0) 
            printf("Received message: %s\n", shared_memory);
    }

    return 0;
}

void get_message(char *message, size_t max_size) {
    printf("Enter a message: ");
    if (fgets(message, max_size, stdin) != NULL) {
        size_t len = strlen(message);
        if (len > 0 && message[len - 1] == '\n') {
            message[len - 1] = '\0';
        }
    }
}
