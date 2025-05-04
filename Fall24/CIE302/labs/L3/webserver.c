#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_child(int child_number) {
    pid_t pid = getpid();
    pid_t parent_pid = getppid();
    printf("I am child number %d, my PID is %d, and my parent's PID is %d\n", child_number, pid, parent_pid);

    // Fork a grandchild process
    pid_t grandchild_pid = fork();

    if (grandchild_pid < 0) {
        perror("Error forking grandchild");
        exit(EXIT_FAILURE);
    } else if (grandchild_pid == 0) {
        // Inside grandchild process
        printf("I am grandchild with PID %d and my parent's PID is %d\n", getpid(), getppid());
        // Send child_number as exit code to parent (child)
        exit(child_number);
    } else {
        // Inside child process
        int grandchild_status;
        waitpid(grandchild_pid, &grandchild_status, 0);
        printf("Grandchild exit code: %d\n", WEXITSTATUS(grandchild_status));
        // Send child_number as exit code to parent (server)
        exit(child_number);
    }
}

int main() {
    int n;
    printf("Enter the number of simultaneous client connections (n): ");
    scanf("%d", &n);

    // Validate input
    if (n <= 0) {
        printf("Invalid input. Exiting.\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i <= n; ++i) {
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("Error forking child");
            return EXIT_FAILURE;
        } else if (child_pid == 0) {
            // Inside child process
            handle_child(i);
        }
        // Parent continues to fork next child
    }

    // Parent process waits for all children to finish
    for (int i = 0; i < n; ++i) {
        int child_status;
	//pid_t child_pid = wait(&child_status);
        pid_t child_pid = waitpid(getpid(), &child_status, 0);
        printf("Child exit code: %d\n", WEXITSTATUS(child_status));
    }

    return EXIT_SUCCESS;
}
