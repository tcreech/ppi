/* Program to compute Pi using Monte Carlo methods */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

#define FPTYPE double

static double rtclock(){
   struct timeval Tp;
   gettimeofday (&Tp, NULL);
   return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}

int main(int argc, char** argv)
{
   long int niter=0;
   long int i,count=0; /* # of points in the 1st quadrant of unit circle */
   FPTYPE pi;
   double startt, stopt;

   if(argc < 2){
      printf("Usage: %s ITERATIONS    # 2^ITERATIONS iterations will be used.\n", argv[0]);
      exit(1);
   }

   niter = atoi(argv[1]);
   niter = pow(2, niter);
   printf("Estimating pi with %ld iterations...\n", niter);
   startt = rtclock();

   /* initialize random numbers */
   count=0;

#pragma omp parallel
   {
      unsigned int seed = ((time(NULL)) ^ omp_get_thread_num());

#pragma omp for private(i) reduction(+:count) schedule(static)
      for ( i=0; i<niter; i++) {
         FPTYPE x = (FPTYPE)rand_r(&seed)/RAND_MAX;
         FPTYPE y = (FPTYPE)rand_r(&seed)/RAND_MAX;
         FPTYPE z = x*x+y*y;
         if (z<=1) count++;
      }
   }
   pi=(FPTYPE)count/niter*4;

   stopt = rtclock();

   printf("\tEstimate of pi is %g \n",pi);
   printf("\tTook %g s: %g MFlops/s\n", stopt-startt, (((double)(niter) * 1.0e-6) * 6.0) / (stopt-startt));
   return 0;
}

