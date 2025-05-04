#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_MSG_SIZE 256

// Message structure
struct message {
  long muid; // Message type (client ID)
  char mtext[MAX_MSG_SIZE];
};

int main() {
  key_t up_key = ftok(".", 79);
  key_t down_key = ftok(".", 10);

  // Get message queues
  int up_queue_id = msgget(up_key, 0666);
  int down_queue_id = msgget(down_key, 0666);

  if (up_queue_id == -1 || down_queue_id == -1) {
    perror("msgget failed");
    exit(1);
  }

  while (1) {
    struct message msg;
    msg.muid = getpid() % 10000; // Unique client identifier

    printf("Enter a message: ");
    fgets(msg.mtext, MAX_MSG_SIZE, stdin);
    msg.mtext[strcspn(msg.mtext, "\n")] = 0; // Remove newline character

    // Send message to server on the up queue
    if (msgsnd(up_queue_id, &msg, sizeof(msg.mtext), 0) == -1) {
      perror("msgsnd failed");
      exit(1);
    }

    // Receive modified message from server on the down queue
    if (msgrcv(down_queue_id, &msg, sizeof(msg.mtext), msg.muid, 0) == -1) {
      perror("msgrcv failed");
      exit(1);
    }

    printf("Modified message from server: %s\n", msg.mtext);
  }

  return 0;
}
