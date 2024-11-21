#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    printf("System running time is %d\n", uptime());

    exit(0);
}
