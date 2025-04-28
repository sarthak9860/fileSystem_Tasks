#include <stdio.h>
#include <stdlib.h>

void cat_file(FILE *fp) {
	int c;
	while ((c = fgetc(fp)) != EOF) {
		putchar(c);
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		cat_file(stdin);
	} 
	else {
		for (int i = 1; i < argc; i++) {
			FILE *fp = fopen(argv[i], "r");
			if (fp == NULL) {
				fprintf(stderr, "cat: cannot open %s\n", argv[i]);
				continue;
			}
			cat_file(fp);
			fclose(fp);
		}
	}

	return 0;
}

