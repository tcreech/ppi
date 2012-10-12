ppi
===

Super simple Monte-carlo pi estimation. Parallelized trivially with ptheads and OpenMP. For the simplest of benchmarking. To be clear, this is an awful benchmark, but I just needed something reasonably portable which can give an idea of the upper limit of a machine's floating point capabilities.

Beware static scheduling and load imbalance. Note that you can change OpenMP's scheduling easily with an environment variable, but you're kind of stuck with pthreads.

Example invocation
------------------

To run 2^30 simulations distributed over all of your processors (with OpenMP):

    $ ./ppi 30
    Estimating pi with 1073741824 iterations...
            Estimate of pi is 3.14159
            Took 4.59223 s: 1402.9 MFlops/s


