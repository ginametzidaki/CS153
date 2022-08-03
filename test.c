#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
	
    int PScheduler(void);
    //int DonationTest(void);
    printf(1, "\n This program tests the correctness of your lab#2\n");
    

    printf(1, "\n\n~~~~~USING GIVEN TEST~~~~~\n\n");
	PScheduler();
    /*printf(1, "\n\n~~~~~PRIORITY DONATION TEST~~~~~\n\n");
    DonationTest();*/

	return 0;

}

int PScheduler(void){
		 
    // use this part to test the priority scheduler. Assuming that the priorities range between range between 0 to 31
    // 0 is the highest priority and 31 is the lowest priority.  

    int pid;
    int i,j,k;
  
    printf(1, "\n  Step 2: testing the priority scheduler and setpriority(int priority)) system call:\n");
    printf(1, "\n  Step 2: Assuming that the priorities range between range between 0 to 31\n");
    printf(1, "\n  Step 2: 0 is the highest priority. All processes have a default priority of 10\n");
    printf(1, "\n  Step 2: The parent processes will switch to priority 0\n");

    printf(1, "This is the current parent priority: %d\n",getpriority());
    setpriority(0);
    printf(1, "This is the current parent priority after doing setpriority(0): %d\n",getpriority());

    for (i = 0; i <  3; i++) {
	    pid = fork();
	    if (pid > 0 ) {
		    continue;
        }

	    else if ( pid == 0) {

            setpriority(30-10*i);
            //getpriority();
            printf(1, "This is process %d's priority: %d\n",getpid(),getpriority());

            for (j=0;j<50000;j++) {

                for(k=0;k<1000;k++) {
                    asm("nop"); 
                }
                /*if(j==49999) {
                    printf(1, "This is the process %d's priority in for loop: %d\n",getpid(), getpriority());
                }*/
            }
            printf(1, "\n child# %d with priority %d has finished! \n",getpid(),30-10*i);		
            exit(0);
        }
        
        else {
            printf(2," \n Error \n");
        }
	}

	if(pid > 0) {

		for (i = 0; i <  3; i++) {
			wait(0);
		}
        printf(1,"\n if processes with highest priority finished first then its correct \n");
    }

    printf(1, "Current process priority: %d\n", getpriority());
	exit(0);		
	return 0;
}
/*
int DonationTest(void) {
    int pid, pid1;
    int exit_status;

    setpriority(10);
    printf(1, "Parent process %d has priority %d\n", getpid(), getpriority());
    pid = fork();
    if(pid == 0) {
        setpriority(30);
        printf(1, "Child process %d has priority %d\n", getpid(), getpriority());
        pid1 = fork();
    }
    if(pid1 == 0) {
        setpriority(20);
        printf(1, "Grandchild process %d has priority %d\n", getpid(), getpriority());
    }
    if(pid && pid1) {
        wait(&exit_status);
    }

    if(pid1 == 0) {
        printf(1, "Grandchild exiting\n");
        exit(0);
    }

    if(pid == 0) {
        printf(1, "Child exiting\n");
        exit(0);
    }

    printf(1, "Process %d priority: %d\n", getpid(), getpriority());
    exit(0);


    return 0;
}*/


/* LAB 1 TEST
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
*/