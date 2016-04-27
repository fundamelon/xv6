#include "types.h"
#include "user.h"

int main(int argc, char** argv) {
    int pids[10];
    int i = 0;
    while(i < 10) {
        int pid = fork();
        if(pid == 0) {
            printf(1, "-");
            exit(0);
        }
        
        printf(1, "Created child PID: %d\n", pid);
        pids[i] = pid;

        i++;
    }
    
    int status;
    i = 0;
    while(i < 10) {
        waitpid(pids[i], &status, 0);
        if(status != 0) exit(status);
        else printf(1, "Child PID: %d exited with status %d\n", pids[i], status);
        i++;
    }

    exit(0);
}
