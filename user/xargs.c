#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

/**
 * xargs 函数用于将从标准输入读取的数据作为参数添加到一个命令中，并执行该命令。
 *
 * @param argc 命令行参数的数量，不包括通过标准输入读取的参数。
 * @param argv 命令行参数的数组，不包括通过标准输入读取的参数。
 * @param max_arg 从标准输入读取的参数，将被添加到新命令的参数列表中。
 */
void xargs(int argc, char *argv[], char *max_arg)
{
    // 2. 创建一个新的参数列表，包含原始参数和从标准输入读取的参数
    char *new_argv[argc + 2];
    for (int i = 0; i < argc; i++)
    {
        new_argv[i] = argv[i];
    }
    new_argv[argc] = max_arg;
    new_argv[argc + 1] = 0; // 参数列表的结束符

    // 3. 创建子进程并执行新命令
    if (fork() == 0)
    {
        exec(new_argv[1], &new_argv[1]); // 替换当前进程的图像，执行新命令
        exit(0);                         // 子进程执行失败时退出
    }
    else
    {
        wait(0); // 父进程等待子进程完成
    }
}

/**
 * main 函数是程序的入口点。它从标准输入读取数据，并将其作为参数传递给 xargs 函数。
 * 当读取到换行符时，调用 xargs 函数，并重置相关变量以准备下一次读取。
 *
 * @param argc 命令行参数的数量。
 * @param argv 命令行参数的数组。
 * @return 程序退出状态。
 */
int main(int argc, char *argv[])
{
    char max_arg[MAXARG]; // 用于存储从标准输入读取的数据
    char temp_char;       // 临时字符变量，用于逐字符读取标准输入
    int count = 0;        // 记录已读取字符的数量

    // 1. 从标准输入读取数据
    while (read(0, &temp_char, sizeof(char)))
    {
        if (temp_char == '\n') // 检查是否读取到换行符
        {
            xargs(argc, argv, max_arg);          // 调用 xargs 函数，执行新命令
            count = 0;                           // 重置计数器
            memset(max_arg, 0, sizeof(max_arg)); // 清空 max_arg 缓冲区
            continue;                            // 继续读取下一个命令
        }
        max_arg[count++] = temp_char; // 将读取的字符添加到 max_arg 缓冲区
    }

    exit(0); // 正常退出程序
}