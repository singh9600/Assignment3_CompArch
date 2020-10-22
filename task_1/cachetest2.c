/* do not add other includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double getTime(){
  struct timeval t;
  double sec, msec;
  
  while (gettimeofday(&t, NULL) != 0);
  sec = t.tv_sec;
  msec = t.tv_usec;
  
  sec = sec + msec/1000000.0;
  
  return sec;
}
 
/* for task 1 only */
void usage(void)
{
	fprintf(stderr, "Usage: cachetest1/2 [--repetitions M] [--array_size N]\n");
	exit(1);
}

int main (int argc, char *argv[])
{
  double t1, t2; 
  
  /* variables for task 1 */
  unsigned int M = 1000;
  unsigned int N = 256*1024; 
  unsigned int i;
	
  /* declare variables; examples, adjust for task */
  int *a;
  int *b;
  int randNum1 = 0;
  int randNum2 = 0;
  int temp = 0;
  long int sum = 0;
  
  /* parameter parsing task 1 */
  for(i=1; i<(unsigned)argc; i++) {
	  if (strcmp(argv[i], "--repetitions") == 0) {
		  i++;
		  if (i < argc)
			  sscanf(argv[i], "%u", &M);
		  else
			  usage();
	  } else if (strcmp(argv[i], "--array_size") == 0) {
		  i++;
		  if (i < argc)
			  sscanf(argv[i], "%u", &N);
		  else
			  usage();
	  } else usage();
  }

    
  /* allocate memory for arrays; examples, adjust for task */
	a = (int*) malloc (N * sizeof(int));
  b = (int*) malloc (N * sizeof(int));

	 /* initialise arrray elements */
  for(int index = 0; index < N; index++) {
    a[index] = index + 2;
    b[index] = index;
  }

  /* randomise array b */
  for(int index = 0; index < 2*N; index++) {
    randNum1 = (rand() % N);
    randNum2 = (rand() % N);
    temp = b[randNum1];
    b[randNum1] = b[randNum2];
    b[randNum2] = temp;
  }
	 
  t1 = getTime();
  /* code to be measured goes here */
  /***************************************/
	for(int count = 0; count < M; count++) {
    sum = 0;
    for(int index = 0; index < N; index++) {
      sum = sum + a[b[index]];
    }
  }
  /***************************************/
	t2 = getTime(); 
  
  double timePerIter = (1000000000)*(t2 - t1)/(M);
  timePerIter = timePerIter/N;

  /* output; examples, adjust for task */
  printf("time: %6.5f secs\n",(t2 - t1));
  printf("time per iteration: %6.5lf nanosecs\n",timePerIter);
  printf("size of array in KB: %d KB\n", 4*N/1024);
  printf("sum: %ld\n", sum);

  /* IMPORTANT: also print the result of the code, e.g. the sum, 
   * otherwise compiler might optimise away the code */
  
  /* free memory; examples, adjust for task */
  free(a);
  free(b);

  return 0;  
}
