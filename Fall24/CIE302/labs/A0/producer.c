#include "common.h"

int produce_rate;
int write_index = 0;
int total_produced = 0;

void cleanup() {
  memory_cleanup();
  printf("Producer: Cleaned up resources.\n");
}

void termination_handler(int sig) {
  cleanup();
  exit(0);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <buffer_size> <produce_rate>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  buffer_size = atoi(argv[1]);
  produce_rate = atoi(argv[2]);

  // Setup signal handling for cleanup
  signal(SIGINT, termination_handler);

  // Allocate shared memory and initialize semaphores
  memory_init();
  printf("Producer: Starting production...\n");

  while (1) {
    int item = rand() % 100; // Produce a random item

    // Wait for space
    sem_wait(space);

    // Wait for mutex
    sem_wait(mutex);

    // Critical section: Add item to the buffer
    buffer[write_index] = item;
    printf("Producer: Produced item %d at index %d (total: %d)\n", item, write_index, total_produced);
    write_index = (write_index + 1) % buffer_size;
    total_produced++;

    // Signal mutex
    sem_post(mutex);

    // Signal that an item is available
    sem_post(items);

    // Sleep for the produce rate
    usleep(1000000 / produce_rate);
  }

  cleanup();
  return 0;
}
