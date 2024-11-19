/*
提示：
1. 查看 user/ls.c：
查看 xv6 源代码中 user/ls.c 文件的实现，了解如何读取目录内容。

2. 使用递归来遍历子目录：
由于需要递归地搜索子目录，您需要在 find 命令的实现中使用递归函数。

3. 避免递归进入 "." 和 ".."：
在遍历目录时，不要递归进入当前目录（.）和上级目录（..）。

4. 文件系统持久性：
xv6 中的文件系统更改在 qemu 运行之间是持久的。如果您需要一个干净的文件系统，可以先运行 make clean，然后再运行 make qemu。

5. 使用 C 字符串：
您需要使用 C 字符串函数，可以参考 K&R 的《C程序设计语言》第 5.5 节。

6. 字符串比较：
在 C 语言中，不要用 == 来比较字符串，应该使用 strcmp() 函数。
*/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *file_name)
{
    char buf[512], *p; // 缓冲区和指针，用于构建路径
    int fd;            // 文件描述符
    struct dirent de;  // 目录项结构体
    struct stat st;    // 文件状态结构体

    // 尝试打开目录或文件
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "ls: cannot open %s\n", path); // 打开失败，输出错误信息
        return;                                   // 暂时认为此处是 递归结束出口
    }

    // 获取文件状态
    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "ls: cannot stat %s\n", path); // 获取状态失败，输出错误信息
        close(fd);                                // 关闭文件描述符
        return;
    }

    // 根据文件类型处理
    switch (st.type)
    {
    case T_FILE: // 如果是文件
        printf("%s\n", path); // 输出文件信息
        break;

    case T_DIR: // 如果是目录
        // 检查路径长度是否超过缓冲区大小
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("ls: path too long\n"); // 路径过长，输出错误信息
            break;
        }

        // 构建新的路径
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';

        // 读取目录项
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {

            // 跳过 . 和 ..
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            {
                continue;
            }

            if (de.inum == 0) // 跳过无效的目录项
                continue;

            // 将目录项名称复制到路径中
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;

            // 获取目录项的状态
            if (stat(buf, &st) < 0)
            {
                printf("ls: cannot stat %s\n", buf); // 获取状态失败，输出错误信息
                continue;
            }

            // 如果是文件夹，就递归，否则就打印
            if (st.type == T_FILE && strcmp(de.name, file_name) == 0)
            {
                printf("%s\n", buf);
            }
            else if (st.type == T_DIR)
            {
                find(buf, file_name);
            }
        }
        break;
    }

    close(fd); // 关闭文件描述符
}

int main(int argc, char *argv[])
{
    char *path = argv[1];      // 路径名
    char *file_name = argv[2]; // 文件名
    find(path, file_name);

    exit(0); // 正常退出
}