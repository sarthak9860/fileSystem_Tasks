#include<stdio.h>
#include<errno.h>

void main() {
   	int i;
   	FILE *f;
   	f = fopen("~hemal/eic", "r");
   	if (f == NULL) {
   		printf("f = null.  errno = %d\n", errno);
    		perror("f1");
  	}
}
