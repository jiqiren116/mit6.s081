
// CMY sleep.c

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    // 如果用户忘记输入参数，应该打印一条错误信息
    if (argc == 1)
    {
        printf("你忘记输入参数了\n");
    }
    
    //定义变量接收参数argv[1]
    char *temp = argv[1];
    int sleep_time = atoi(temp);
    int status = sleep(sleep_time);
    if (status == -1)
    {
        printf("执行sleep系统调用失败\n");
        exit(1);
    }
    
    exit(0);
}
