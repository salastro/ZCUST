#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child1_pid, child2_pid;

// Signal handler for SIGCHLD to manage the exit codes from children
void sigchld_handler(int sig) {
  int status;
  pid_t pid = wait(&status); // Blocking wait for any child process
  // pid_t pid = waitpid(-1, &status, WNOHANG); // Non-blocking wait for any child process

  if (pid == child1_pid) {
    int exit_code = WEXITSTATUS(status); // Get the exit status from child1
    printf("Received exit code %d from child1\n", exit_code);

    if (exit_code == 1) {
      printf("Killing child2\n");
      kill(child2_pid, SIGKILL); // Kill child2 if exit code is 1
    } else {
      printf("Resuming child2\n");
      kill(child2_pid, SIGCONT); // Resume child2 otherwise
    }
  } else if (pid == child2_pid) {
    printf("Child2 exited, terminating parent process\n");
    exit(0); // Terminate the parent when child2 exits
  }
  signal(SIGCHLD, sigchld_handler);
}

int main() {
  // Set up the SIGCHLD handler
  signal(SIGCHLD, sigchld_handler);

  // Fork child1
  if ((child1_pid = fork()) == 0) {
    // Child1 process
    while (1) {
      printf("Child1 PID: %d, Parent PID: %d\n", getpid(), getppid());
      sleep(5);

      int value;
      printf("Child1: Enter a value: ");
      scanf("%d", &value);

      exit(value); // Send the value as the exit code to the parent
    }
  }

  // Fork child2
  if ((child2_pid = fork()) == 0) {
    // Child2 process
    printf("Child2 PID: %d, Parent PID: %d\n", getpid(), getppid());
    // kill(getpid(), SIGSTOP); // Suspend itself
    raise(SIGSTOP); // Suspend itself

    printf("Child2 process is resumed\n");
    exit(0); // Exit when resumed
  }

  // Parent process loop
  while (1) {
    // Parent doing its own work in an infinite loop
  }

  return 0;
}
