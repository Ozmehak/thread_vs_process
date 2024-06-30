#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "thread_vs_process_utils.h"

/*Return type pointer to void so can be any return type, argument a voidpointer
 * so any argument can be passed.*/
void * thread_timer(void * arg) { return NULL; }

void * process_timer(void * arg) { exit(0); }

void measure_thread()
{
  struct timespec start, end;
  pthread_t pthread_id;

  /* get a monotonic timestamp and store it in start*/
  clock_gettime(CLOCK_MONOTONIC, &start);

  for (int i = 0; i < ITERATIONS; i++)

  {
    int thread = pthread_create(&pthread_id, NULL, thread_timer, NULL);
    if (thread != 0)
    {
      fprintf(stderr, "Could not create thread! \n");
      exit(1);
    }

    pthread_join(pthread_id, NULL);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);

  long seconds = end.tv_sec - start.tv_sec;
  long nanoseconds = end.tv_nsec - start.tv_nsec;
  double elapsed = seconds + nanoseconds * 1e-9;
  printf("Average thread overhead: %f microseconds\n", (elapsed / ITERATIONS) * 1e6);
}

void measure_process()
{
  struct timespec start, end;
  pid_t pid;

  clock_gettime(CLOCK_MONOTONIC, &start);

  for (int i = 0; i < ITERATIONS; i++)
  {
    pid = fork();
    if (pid < 0)
    {
      fprintf(stderr, "Could not create process! \n");
      exit(1);
    }

    if (pid == 0)
    {
      exit(0);
    }
    else if (pid == 1)
    {
      exit(0);
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &end);

  long seconds = end.tv_sec - start.tv_sec;
  long nanoseconds = end.tv_nsec - start.tv_nsec;
  double elapsed = seconds + nanoseconds * 1e-9;
  printf("Average process overhead: %f microseconds\n", (elapsed / ITERATIONS) * 1e6);
}

int main()
{
  printf("Measuring thread...\n");
  measure_thread();
  printf("Measuring process ...\n");
  measure_process();
  return 0;
}
