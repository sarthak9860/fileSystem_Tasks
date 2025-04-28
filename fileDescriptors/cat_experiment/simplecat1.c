#include <stdio.h>

void main(){
	char c;
	c = getchar();
	while(c != EOF) {
		putchar(c);
		c = getchar();
	}
}
