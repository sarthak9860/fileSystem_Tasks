// Question

/** REQUIRED HEADER FILES **/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include"../include/head.h"

/*
 * Name of the function:
 * Author: Sarthak Bosamiya
 * Created: 21-04-2025
 * Modified: 21-04-2025
*/

void task_1(){
	int fd = open("file_hole.txt", O_WRONLY | O_CREAT,0767);
	if (fd<0){
		perror("Open");
		return;
	}
	char *str1 = "Start";
	if(write(fd, str1, 5)!=5){
		perror("Write");
		return;
	}
	if(lseek(fd, 4096, SEEK_CUR)<0){
		perror("Lseek");
		return;
	}
	char* str2 = "End";
	if(write(fd, str2, 3)!=3){
		perror("Write");
		return;
	}
	close(fd);
	printf("File with 4KB hole is created\n");
}
