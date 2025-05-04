#include <ctype.h>
#include <signal.h>
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

int up_queue_id, down_queue_id;

// Function to convert uppercase to lowercase and vice versa
void conv(char *msg, int size) {
  for (int i = 0; i < size; ++i) {
    if (islower(msg[i])) {
      msg[i] = toupper(msg[i]);
    } else if (isupper(msg[i])) {
      msg[i] = tolower(msg[i]);
    }
  }
}

// Signal handler to cleanup message queues on exit
void cleanup(int signum) {
  msgctl(up_queue_id, IPC_RMID, NULL);
  msgctl(down_queue_id, IPC_RMID, NULL);
  printf("\nServer terminated and message queues cleaned up.\n");
  exit(0);
}

int main() {
  key_t up_key = ftok(".", 79);
  key_t down_key = ftok(".", 10);

  // Create message queues
  up_queue_id = msgget(up_key, IPC_CREAT | 0666);
  down_queue_id = msgget(down_key, IPC_CREAT | 0666);

  // Set up signal handler for cleanup
  signal(SIGINT, cleanup);

  struct message msg;
  printf("Server is running...\n");

  while (1) {
    // Receive message from the up queue
    if (msgrcv(up_queue_id, &msg, sizeof(msg.mtext), 0, 0) == -1) {
      perror("msgrcv failed");
      exit(1);
    }

    printf("Received message from client %ld: %s\n", msg.muid, msg.mtext);
    conv(msg.mtext, strlen(msg.mtext));

    // Send the converted message back to the client on the down queue
    if (msgsnd(down_queue_id, &msg, sizeof(msg.mtext), 0) == -1) {
      perror("msgsnd failed");
      exit(1);
    }
    printf("Converted message sent to client %ld: %s\n", msg.muid, msg.mtext);
  }

  return 0;
}
