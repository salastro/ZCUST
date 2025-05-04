#include "common.h"

int consume_rate;
int read_index = 0;
int total_consumed = 0;

void cleanup() {
  memory_cleanup();
  printf("Consumer: Cleaned up resources.\n");
}

void termination_handler(int sig) {
  cleanup();
  exit(0);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <buffer_size> <consume_rate>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  buffer_size = atoi(argv[1]);
  consume_rate = atoi(argv[2]);

  // Setup signal handling for cleanup
  signal(SIGINT, termination_handler);

  // Allocate shared memory and initialize semaphores
  memory_init();
  printf("Consumer: Starting consumption...\n");

  while (1) {
    // Wait for an item
    sem_wait(items);

    // Wait for mutex
    sem_wait(mutex);

    // Critical section: Consume an item from the buffer
    int item = buffer[read_index];
    printf("Consumer: Consumed item %d from index %d (total: %d)\n", item, read_index, total_consumed);
    read_index = (read_index + 1) % buffer_size;
    total_consumed++;

    // Signal mutex
    sem_post(mutex);

    // Signal that space is available
    sem_post(space);

    // Sleep for the consume rate
    usleep(1000000 / consume_rate);
  }

  cleanup();
  return 0;
}
