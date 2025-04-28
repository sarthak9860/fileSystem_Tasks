#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024

void cat_fd(int fd) {
	char buf[BUF_SIZE];
	ssize_t bytes_read;

	while ((bytes_read = read(fd, buf, BUF_SIZE)) > 0) {
		if (write(1, buf, bytes_read) != bytes_read) {
			perror("cat: write error");
			exit(1);
		}
	}

	if (bytes_read < 0) {
		perror("cat: read error");
		exit(1);
	}
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		cat_fd(0);
	} 
	else {
		for (int i = 1; i < argc; i++) {
			int fd = open(argv[i], O_RDONLY);
			if (fd < 0) {
				fprintf(stderr, "cat: cannot open %s: %s\n", argv[i], strerror(errno));
				continue;
			}

			cat_fd(fd);
			close(fd);
		}
	}
	return 0;
}

