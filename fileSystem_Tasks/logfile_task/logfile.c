#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define LOG_FILE "./logs/logfile"

void write_to_fill_log() {
    	char *username;
    	long t;
    	FILE *f;
    	username = getenv("USER");
    	t = time(0);
    	f = fopen(LOG_FILE, "a");
    	if (!f) {
        	perror("fopen");
        	return;
    	}
    	fprintf(f, "%s %ld\n", username ? username : "unknown", t);
    	fclose(f);
}

int main(){
	write_to_fill_log();
	return 0;
}

