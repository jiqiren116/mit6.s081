/*
 * 这是我写的第一个程序，是跟着网上抄的，具体是https://blog.csdn.net/ConstineWhy/article/details/123313378
*/

#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

int main()
{
    printf("Hello World!!!\n");
    exit(0); // 不能用return 0; 会报错
}