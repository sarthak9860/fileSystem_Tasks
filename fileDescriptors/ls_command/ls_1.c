#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#define MAX_FILES 1024

typedef struct {
	char name[PATH_MAX];
	off_t size;
	mode_t mode;
} FileEntry;

int compare_names(const void *a, const void *b) {
	return strcmp(((FileEntry *)a)->name, ((FileEntry *)b)->name);
}

void list_files_sorted(const char *path, int show_flags) {
	DIR *dir = opendir(path);
	if (!dir) {
		perror("opendir");
		return;
	}

	FileEntry files[MAX_FILES];
	int count = 0;
	struct dirent *entry;
	struct stat st;
	char fullpath[PATH_MAX];

	while ((entry = readdir(dir)) != NULL && count < MAX_FILES) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
		if (lstat(fullpath, &st) == -1) {
			perror("lstat");
			continue;
		}
		strncpy(files[count].name, entry->d_name, PATH_MAX - 1);
		files[count].size = st.st_size;
		files[count].mode = st.st_mode;
		count++;
	}

	closedir(dir);
	qsort(files, count, sizeof(FileEntry), compare_names);

	for (int i = 0; i < count; i++) {
		printf("%-30s %10ld", files[i].name, (long)files[i].size);

		if (show_flags) {
			if (S_ISDIR(files[i].mode))
				printf("/");
			else if (S_ISLNK(files[i].mode))
				printf("@");
			else if (files[i].mode & S_IXUSR)
				printf("*");
		}

		printf("\n");
	}
}

off_t disk_usage(const char *path) {
	DIR *dir = opendir(path);
	if (!dir) {
		perror("opendir");
		return 0;
	}

	struct dirent *entry;
	struct stat st;
	char fullpath[PATH_MAX];
	off_t total_size = 0;

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
		if (lstat(fullpath, &st) == -1) {
			perror("lstat");
			continue;
		}

		if (S_ISLNK(st.st_mode)) {
			continue;
		} else if (S_ISDIR(st.st_mode)) {
			total_size += disk_usage(fullpath);
		} else {
			total_size += st.st_size;
		}
	}

	closedir(dir);
	return total_size;
}

int main(int argc, char *argv[]) {
	int show_flags = 0;
	int show_summary = 0;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-F") == 0) {
			show_flags = 1;
		} 
		else if (strcmp(argv[i], "-s") == 0) {
			show_summary = 1;
		} 
		else {
			fprintf(stderr, "Unknown option: %s\n", argv[i]);
			return 1;
		}
	}

	list_files_sorted(".", show_flags);

	if (show_summary) {
		off_t total = disk_usage(".");
		printf("\nTotal bytes used (excluding symlinks): %ld\n", (long)total);
	}

	return 0;
}

