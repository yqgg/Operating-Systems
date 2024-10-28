#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> /* pid_t */

int main() {
    pid_t pid, pid2, pid3, pid4;

    // Create the first child process
    pid = fork();
    if (pid) {
        pid2 = fork();
        if(pid2) {
            // Parent code
            printf("Parent A PID: %d\n", getpid());
            pid3 = fork();
            if(pid3==0) {
                printf("Child c PID: %d\n", getpid());
            }
        } else {
            printf("Child a PID: %d\n", getpid());
        }
        
    } else {
        // Child A code
        //printf("Child A PID: %d\n", getpid());
        pid4 = fork();
        if(pid4) {
            printf("Parent B PID: %d\n", getpid());
        } else {
            printf("Child b PID: %d\n", getpid());
        }
    }
    wait(0);
    wait(0);
    wait(0);
    return 0;
}
