#include <stdio.h>
#include<stdlib.h>
         
void main(int argc, char **argv)         
{                                   
  int bufsize;                      
  char *c;                          
  int i;                                                                 
  bufsize = atoi(argv[1]);          
  c = malloc(bufsize*sizeof(char)); 
  i = 1;                            
  while (i > 0) {                   
    i = fread(c, 1, bufsize, stdin); 
    if (i > 0) fwrite(c, 1, i, stdout);
  }                              
}
