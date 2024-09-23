
// exec.c: replace a process with an executable file

#include "kernel/types.h"
#include "user/user.h"

int main()
{
    char *argv[] = {"echo", "this", "is", "echo", 0};

    int n = exec("echo", argv);
    if (n == -1)
    {
        printf("exec failed!\n");
        exit(1);
    }
    

    printf("exec failed!\n");

    exit(0);
}