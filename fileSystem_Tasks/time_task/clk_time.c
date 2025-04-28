/* tt.c */
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>

typedef struct {
  clock_t        clock_val;
  time_t         time_val;
  struct timeval gettime_val;
  struct tms     times_val; 
} all_times;

void get_time(all_times * t)
{
  t->clock_val = clock();
  t->time_val = time(NULL);
  gettimeofday(&(t->gettime_val), NULL);
  times(&(t->times_val));
}

void print_duration(all_times * t1, all_times * t2)
{
  float elapsed;
  long clktck, nticks; 

  nticks = t2->clock_val - t1->clock_val;
  elapsed = (float)nticks/CLOCKS_PER_SEC; 
  fprintf(stderr,"clock: %f sec\n", elapsed);

  nticks = t2->time_val - t1->time_val;
  fprintf(stderr,"time: %ld sec\n", nticks);

  elapsed = t2->gettime_val.tv_sec - t1->gettime_val.tv_sec;
  elapsed += (t2->gettime_val.tv_usec - t1->gettime_val.tv_usec)/1e6;
  fprintf(stderr,"gettimeofday: %f sec\n", elapsed);

  clktck = sysconf(_SC_CLK_TCK);
  nticks = t2->times_val.tms_utime - t1->times_val.tms_utime;
  elapsed = (float)nticks/clktck;  
  fprintf(stderr,"times: %f sec user time\n", elapsed);

  nticks = t2->times_val.tms_stime - t1->times_val.tms_stime;
  elapsed = (float)nticks/clktck;  
  fprintf(stderr,"times: %f sec system time\n", elapsed);
}

long simplecat()
{
  char c;
  int i;
  long cnt = 0;

  i = fread(&c, 1, 1, stdin);
  while(i > 0) {
    fwrite(&c, 1, 1, stdout);
    i = fread(&c, 1, 1, stdin);
    cnt ++;
  }

  return cnt;
}

int main(void)
{
  int totalbytes;

  all_times a1, a2;

  get_time(&a1);

  totalbytes = simplecat();

  get_time(&a2);
  print_duration(&a1, &a2);

  fprintf(stderr, "total of %f MiB\n", totalbytes/1e6);

  return 0;
}
