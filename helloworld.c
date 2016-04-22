#include "types.h"
#include "user.h"

int main(int argc, char** argv) {
    int pid = fork();
    if(pid == 0) {
        printf(1, "Child\n");
        exit(0);
    } else {
        wait(NULL);
        printf(1, "Parent\n");
    }
    exit(0);
}
