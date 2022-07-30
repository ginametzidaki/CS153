#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) 
{
   int pid, ret_pid, exit_status;
   int i;

    printf(1, "TESTING GET PID CALLS:\n");
    printf(1, "getpid: %d\n", getpid());
    printf(1, "getppid: %d\n", getppid());
    printf(1, "\n");

    
    printf(1, "TESTING EXIT AND WAIT CALLS:\n");
    for (i = 0; i < 2; i++) 
    {
        pid = fork();
        if(pid == 0) { //only the child executed this code
            if(i == 0) {
                printf(1, "\nThis is child with PID# %d and I will exit with status %d\n", getpid(), 10);
                exit(10);
            }
            else {
                printf(1, "\nThis is child with PID# %d and I will exit with status %d\n", getpid(), -1);
                exit(-1);
            }
        }
        else if(pid > 0) {
            ret_pid = wait(&exit_status); 
            printf(1, "\nThis is the parent: child with PID# %d has exited with status %d\n", ret_pid, exit_status);
        }
        else {
            printf(2, "\nError using fork\n");
            exit(-1);
        }
    }
    printf(1, "\n");

    printf(1, "TESTING PS CALL:\n");
    printf(1, "%d", ps());

    exit(10);
}
