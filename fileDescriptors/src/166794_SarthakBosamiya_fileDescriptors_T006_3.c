// Question

/** REQUIRED HEADER FILES **/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include"../include/head.h"

/*
 * Name of the function:
 * Author: Sarthak Bosamiya
 * Created: 21-04-2025
 * Modified: 21-04-2025
*/

void print_file_type(const struct stat *st) {
    	if (S_ISREG(st->st_mode)) {
        	printf("Regular file");
    	} 
	else if (S_ISDIR(st->st_mode)) {
        	printf("Directory");
    	} 
	else if (S_ISLNK(st->st_mode)) {
        	printf("Symbolic link");
    	} 
	else if (S_ISCHR(st->st_mode)) {
        	printf("Character device");
    	}
       	else if (S_ISBLK(st->st_mode)) {
        	printf("Block device");
    	} 
	else if (S_ISFIFO(st->st_mode)) {
        	printf("FIFO/pipe");
    	} 
	else if (S_ISSOCK(st->st_mode)) {
        	printf("Socket");
    	} 
	else {
        	printf("Unknown type");
    	}
}

void task_3(int argc, char *argv[]) {
    	if (argc != 2) {
        	fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        	return;
    	}
    	DIR *dir = opendir(argv[1]);
    	if (dir == NULL) {
        	fprintf(stderr, "Error opening directory '%s': %s\n", argv[1], strerror(errno));
        	return;
    	}
    	struct dirent *entry;
    	char path[4096];
    	struct stat st;
    	while ((entry = readdir(dir)) != NULL) {
        	snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
        		if (lstat(path, &st) == -1) {
            			fprintf(stderr, "Error stating '%s': %s\n", path, strerror(errno));
            		continue;
        	}
        	printf("%-30s : ", entry->d_name);
        	print_file_type(&st);
        	printf("\n");
    	}
    	closedir(dir);
}

