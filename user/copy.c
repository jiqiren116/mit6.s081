
// copy.c: copy input to output.

#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  char buf[64];

  while(1){
    int n = read(0, buf, sizeof(buf));
    //当输入exit时直接退出copy程序。
    if (buf[0] == 'e'
     && buf[1] == 'x'
     && buf[2] == 'i'
     && buf[3] == 't')
    {
        break;
    }

    if(n <= 0)
    {
      printf("copy: read error\n");
      break;
    }
    // write(1, buf, n);
    if (write(1, buf, n))
    {
      printf("copy: write error\n");
      break;
    }
    
  }

  exit(0);
}