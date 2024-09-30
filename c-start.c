#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  char *panel = "panel.py"; 

  // Create a new process to run the Python program
  if (fork() == 0) {
    // Child process: execute the Python program
    execlp("python3", "python3", panel, NULL);
    // If execlp fails, print an error message
    perror("execlp failed");
    exit(1);
  } else {
    // Parent process: wait for the child process to finish
    wait(NULL);
    // Close the parent process
    exit(0);
  }

  return 0;
}
