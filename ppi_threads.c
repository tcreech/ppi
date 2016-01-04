/* Program to compute Pi using Monte Carlo methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define FPTYPE double

struct intrange_s {
   long int start;
   long int end;
} intrange_s;

typedef struct intrange_s intrange;

static double rtclock(){
   struct timeval Tp;
   gettimeofday (&Tp, NULL);
   return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}

void* thread_body(void *data){
   long int privcount = 0;
   intrange *r = (intrange*)data;
   long int low = r->start;
   long int high = r->end;
   long int i;

   unsigned int seed = ((time(NULL)) ^ low);
   for ( i=low; i<high; i++) {
      FPTYPE x = (FPTYPE)rand_r(&seed)/RAND_MAX;
      FPTYPE y = (FPTYPE)rand_r(&seed)/RAND_MAX;
      FPTYPE z = x*x+y*y;
      if (z<=1) privcount++;
   }

   return (void*)privcount;
}

int main(int argc, char** argv)
{
   long int niter=0;
   int threads=1;
   long int i,count=0; /* # of points in the 1st quadrant of unit circle */
   FPTYPE pi;
   double startt, stopt;

   if(argc < 3){
      printf("Usage: %s THREADS ITERATIONS    # 2^ITERATIONS iterations will be used.\n", argv[0]);
      exit(1);
   }

   threads = atoi(argv[1]);
   niter = atoi(argv[2]);
   niter = pow(2, niter);
   printf("Estimating pi with %ld iterations on %d threads...\n", niter, threads);
   startt = rtclock();

   /* initialize random numbers */
   count=0;

   intrange *range_list = malloc(sizeof(intrange)*threads);
   long int per_thread = niter / threads;
   long int extra = niter % threads;
   for(i=0; i<threads; i++){
      range_list[i].start = i*per_thread;
      range_list[i].end   = i*per_thread + per_thread;
   }
   range_list[threads-1].end = niter;

   pthread_t *thread_list = malloc(sizeof(pthread_t)*threads);
   for(i=0; i<threads; i++){
      pthread_create(&(thread_list[i]), NULL, thread_body, &(range_list[i]));
   }

   for(i=0; i<threads; i++){
      void *retval;
      pthread_join(thread_list[i], &retval);
      count += (long int)(retval);
   }

   pi=(FPTYPE)count/niter*4;

   stopt = rtclock();

   printf("\tEstimate of pi is %g \n",pi);
   printf("\tTook %g s: %g MFlops/s\n", stopt-startt, (((double)(niter) * 1.0e-6) * 6.0) / (stopt-startt));
   return 0;
}

