
// CMY pingpong.c

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    char data; // 模拟一字节数据
    int fds1[2], fds2[2];
    pipe(fds1); // 管道1：parent写 child读 parent -> child
    pipe(fds2); // 管道1：child写 parent读 child -> parent

    if (fork() == 0)
    {
        //child 接收数据
        int n = read(fds1[0], &data, 1);
        if (n < 0)
        {
            printf("child read error!\n");
            exit(1);
        }
        printf("%d: received ping\n", getpid());

        //child 发送数据
        write(fds2[1], &data, 1);
    }
    else
    {
        // parent 发送数据
        write(fds1[1], &data, 1);

        //parent 接收数据
        int n = read(fds2[0], &data, 1);
        if (n < 0)
        {
            printf("parent read error!\n");
            exit(1);
        }
        printf("%d: received pong\n", getpid());
    }

    exit(0);
}
