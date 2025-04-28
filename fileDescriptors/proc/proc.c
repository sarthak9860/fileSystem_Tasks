#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printCPUInfo() {
	FILE *fp = fopen("/proc/cpuinfo", "r");
	if (!fp) {
		perror("Error opening /proc/cpuinfo");
		return;
	}
	char line[256];
	int processors = 0;
	char model_name[256] = "";
	int cores = 0;
	while (fgets(line, sizeof(line), fp)) {
		if (strncmp(line, "processor", 9) == 0)
			processors++;
		else if (strncmp(line, "model name", 10) == 0 && model_name[0] == '\0') {
			char *colon = strchr(line, ':');
			if (colon)
				strcpy(model_name, colon + 2);
		}
	       	else if (strncmp(line, "cpu cores", 9) == 0 && cores == 0) {
			sscanf(line, "cpu cores\t: %d", &cores);
		}
	}
	fclose(fp);
	printf("CPU Model: %s", model_name);
	printf("Number of processors: %d\n", processors);
	printf("Number of cores per processor: %d\n", cores);
}

void printKernelVersion() {
	FILE *fp = fopen("/proc/version", "r");
	if (!fp) {
		perror("Error opening /proc/version");
		return;
	}
	char version[256];
	fgets(version, sizeof(version), fp);
	fclose(fp);
	printf("Linux Kernel Version: %s\n", version);
}

void printLastBootTime() {
	FILE *fp = fopen("/proc/uptime", "r");
	if (!fp) {
		perror("Error opening /proc/uptime");
		return;
	}
	double uptime;
	fscanf(fp, "%lf", &uptime);
	fclose(fp);

	time_t now = time(NULL);
	time_t boot = now - (time_t)uptime;
	struct tm *bt = localtime(&boot);
	printf("Last Boot Time: %02d:%02d:%02d, Date: %02d-%02d-%d\n",
			bt->tm_hour, bt->tm_min, bt->tm_sec,
			bt->tm_mday, bt->tm_mon + 1, bt->tm_year + 1900);
}

void printLoadAverage() {
	FILE *fp = fopen("/proc/loadavg", "r");
	if (!fp) {
		perror("Error opening /proc/loadavg");
		return;
	}
	double load1, load5, load15;
	fscanf(fp, "%lf %lf %lf", &load1, &load5, &load15);
	fclose(fp);
	printf("System Load Average (Last 15 minutes): %.2f\n", load15);
}

void printMemoryInfo() {
	FILE *fp = fopen("/proc/meminfo", "r");
	if (!fp) {
		perror("Error opening /proc/meminfo");
		return;
	}
	char label[64];
	long total = 0, free = 0, swapTotal = 0, swapFree = 0;
	while (fscanf(fp, "%63s %ld", label, &total) == 2) {
		if (strcmp(label, "MemTotal:") == 0)
			free = total;
		else if (strcmp(label, "MemAvailable:") == 0)
			total = total;
		else if (strcmp(label, "SwapTotal:") == 0)
			swapTotal = total;
		else if (strcmp(label, "SwapFree:") == 0)
			swapFree = total;
	}
	fclose(fp);
	printf("Usable Memory: %ld kB\n", total);
	printf("Free Memory: %ld kB\n", free);
	printf("Total Swap Space: %ld kB\n", swapTotal);
	printf("Used Swap Space: %ld kB\n", swapTotal - swapFree);
}

void printSwapPartitions() {
	FILE *fp = fopen("/proc/swaps", "r");
	if (!fp) {
		perror("Error opening /proc/swaps");
		return;
	}
	char line[256];
	printf("Swap Partitions and Sizes:\n");
	fgets(line, sizeof(line), fp); // Skip header
	while (fgets(line, sizeof(line), fp)) {
		printf("%s", line);
	}
	fclose(fp);
}

void printCPUTime() {
	FILE *fp = fopen("/proc/stat", "r");
	if (!fp) {
		perror("Error opening /proc/stat");
		return;
	}
	char label[64];
	long user, nice, system;
	fscanf(fp, "%s %ld %ld %ld", label, &user, &nice, &system);
	fclose(fp);
	printf("CPU time in user mode: %ld jiffies\n", user);
	printf("CPU time in kernel mode: %ld jiffies\n", system);
}

void printContextSwitches() {
	FILE *fp = fopen("/proc/stat", "r");
	if (!fp) {
		perror("Error opening /proc/stat");
		return;
	}
	char label[64];
	long ctxt;
	while (fscanf(fp, "%s", label) == 1) {
		if (strcmp(label, "ctxt") == 0) {
			fscanf(fp, "%ld", &ctxt);
			printf("Context Switches: %ld\n", ctxt);
			break;
		} else {
			fgets(label, sizeof(label), fp); // Skip rest of line
		}
	}
	fclose(fp);
}

void printInterrupts() {
	FILE *fp = fopen("/proc/stat", "r");
	if (!fp) {
		perror("Error opening /proc/stat");
		return;
	}
	char label[64];
	long intr;
	while (fscanf(fp, "%s", label) == 1) {
		if (strcmp(label, "intr") == 0) {
			fscanf(fp, "%ld", &intr);
			printf("Interrupts: %ld\n", intr);
			break;
		} else {
			fgets(label, sizeof(label), fp); // Skip rest of line
		}
	}
	fclose(fp);
}

int main() {
	printf("------ System Information ------\n\n");
	printCPUInfo();
	printf("\n");
	printKernelVersion();
	printf("\n");
	printLastBootTime();
	printf("\n");
	printLoadAverage();
	printf("\n");
	printMemoryInfo();
	printf("\n");
	printSwapPartitions();
	printf("\n");
	printCPUTime();
	printf("\n");
	printContextSwitches();
	printInterrupts();
	printf("\n--------------------------------\n");
	return 0;
}

