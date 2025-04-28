// Question

/** REQUIRED HEADER FILES **/

#include<stdio.h>
#include"../include/head.h"

/*
 * Name of the function:
 * Author: Sarthak Bosamiya
 * Created: 21-04-2025
 * Modified: 21-04-2025
*/

#include <stdlib.h>
#include <unistd.h>

void task_5(void)
{
    int i, r, w;
    char msg[12];
    char buf[2] = {0, 0};

    for (i = 0; i < 3; i ++) {
      if ((r = read(i,buf,1))<0) {
         sprintf(msg,"read  f%d:%s",i,buf);
         perror(msg);
      }
      if ((w = write(i,buf,1))<0) {
         sprintf(msg,"write f%d:%s",i,buf);
         perror(msg);
      }
      fprintf(stderr,"%d, r = %d, w = %d, char = %d\n",i,r,w,(int)(buf[0]));
    }
}
