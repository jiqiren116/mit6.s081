// redirect.c: run a command with output redirected

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main()
{
    int pid, status;

    pid = fork();
    if (pid == 0)
    {
        close(1);
        open("output.txt", O_WRONLY|O_CREATE);

        char *argv[] = {"echo", "this", "is", "redirected", "echo", 0};
        int n = exec("echo", argv);
        if (n == -1)
        {
            printf("exec failed!\n");
            exit(1);
        }
    }
    else
    {
        wait(&status);
    }

    exit(0);
}
