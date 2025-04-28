// Question

/** REQUIRED HEADER FILES **/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"../include/head.h"

/*
 * Name of the function:
 * Author: Sarthak Bosamiya
 * Created: 21-04-2025
 * Modified: 21-04-2025
*/

#define BUFSIZE 4096

void task_2(int argc, char* argv[]){
	if (argc != 3){
		printf("Usage: ./exe <filename1> <filename2>\n");
		return;
	}
	int src_fd = open(argv[1], O_RDONLY | O_CREAT, 0755);
	if(src_fd < 0){
                perror("Open src");
                return;
        }
	int dst_fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0755);
	if(dst_fd < 0){
		perror("Open dst");
		return;
	}
	char buffer[BUFSIZE];
	ssize_t bytes_read = 0, bytes_write = 0;
	while((bytes_read=read(src_fd, buffer, BUFSIZE)) > 0){
		if(bytes_read<0){
			perror("Read");
			close(src_fd);
			close(dst_fd);
			return;
		}
		bytes_write = write(dst_fd, buffer, bytes_read);
		if(bytes_write!=bytes_read){
			perror("Write");
			close(src_fd);
                        close(dst_fd);
			return;
		}
	}
	close(src_fd);
        close(dst_fd);
	printf("Content from %s is copied to the %s\n", argv[1], argv[2]);
}
