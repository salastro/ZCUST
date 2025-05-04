#include "helpers.h"
#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void conv(char *msg, int size);
void cleanup_resources(int sig);

int main() {
    // Generate shared memory and semaphores
    shared_memory = generate_shm();
    sem_con = open_semaphore(SEM_CON_NAME, 0);
    sem_pro = open_semaphore(SEM_PRO_NAME, 0);
    sem_lock = open_semaphore(SEM_LOCK_NAME, 1);

    // Handle signals
    signal(SIGINT, cleanup_resources);

    printf("Server running...\n");
    while (1) {
        // Wait for client to write
        printf("Waiting for client...\n");
        sem_wait(sem_pro);

        // Lock shared memory
        sem_wait(sem_lock);

        // Read message
        if (strlen(shared_memory) > 0) {
            char *message = shared_memory;
            printf("Received message: %s\n", message);
            conv(message, strlen(message));
            printf("Converted message: %s\n", message);
            strcpy(shared_memory, message);
        }

        // Unlock shared memory
        sem_post(sem_lock);

        // Notify client
        sem_post(sem_con);
    }

    return 0;
}

void cleanup_resources(int sig) {
    printf("Cleaning up resources...\n");
    destroy_shm();
    destroy_semaphores();
    exit(0);
}

void conv(char *msg, int size) {
    for (int i = 0; i < size; ++i) {
        if (islower(msg[i]))
            msg[i] = toupper(msg[i]);
        else if (isupper(msg[i]))
            msg[i] = tolower(msg[i]);
    }
}
