/*
 * 一直不理解教程中关于管道的案例，这里时间一下
 * https://th0ar.gitbooks.io/xv6-chinese/content/content/chapter0.html#:~:text=p%5B1%5D)%3B%0A%7D-,%E8%BF%99%E6%AE%B5%E7%A8%8B%E5%BA%8F,-%E8%B0%83%E7%94%A8%20pipe
*/

#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

int main()
{
    int p[2];
    char *argv[2];
    argv[0] = "wc";
    argv[1] = 0;
    pipe(p);
    if (fork() == 0)
    {
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        exec("wc", argv);
        // exit(0);
    }
    else
    {
        write(p[1], "hello world\n", 12);
        close(p[0]);
        close(p[1]);
        // wait(0);
    }
    
    exit(0);
}