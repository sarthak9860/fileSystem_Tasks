#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include<unistd.h>
               
void main(int argc, char **argv)                 
{                                                               
  int bufsize;                                     
  char *c;                                                    
  int i;                                                    
                                                                         
  bufsize = atoi(argv[1]);                
  c = malloc(bufsize*sizeof(char)); 
  i = 1;                                                        
  while (i > 0) {                                      
    i = read(0, c, bufsize);        
    if (i > 0) write(1, c, i);     
  }                                                                
}                                  
