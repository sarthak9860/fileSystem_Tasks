#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LOG_FILE "./logs/logfile"

void write_to_fill_log_updated() {
    	char *username;
    	long t;
    	int fd;
    	char log_entry[256];
    	ssize_t len;
    	username = getenv("USER");
    	if (!username){
	       username = "unknown";
	}
	t = time(0);
    	snprintf(log_entry, sizeof(log_entry), "%s %ld\n", username, t);
    	len = strlen(log_entry);
    	fd = open(LOG_FILE, O_WRONLY | O_APPEND | O_CREAT | O_SYNC, 0644);
    	if (fd == -1) {
        	perror("open");
        	return;
    	}
    	if (write(fd, log_entry, len) != len) {
        	perror("write");
	}
    	close(fd);
}

int main(){
	write_to_fill_log_updated();
	return 0;
}
