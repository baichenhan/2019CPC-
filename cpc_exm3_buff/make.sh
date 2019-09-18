make clean
rm -rf *.o
mpicc -host -O3  -OPT:Ofast -W -c -std=c99 -OPT:IEEE_arith=1 benchmark.c
mpicc -host -O3  -OPT:Ofast -W -c -std=c99 -OPT:IEEE_arith=1 check.c
mpicc -host -O3  -OPT:Ofast -W -c -std=c99 -OPT:IEEE_arith=1 stencil-optimized.c
sw5cc -slave -O3  -ver 5.421-sw-gy -O3 -LNO:simd=1:simd_report=2  -w -c -std=c99 -OPT:IEEE_arith=1 slave.c
#sw5cc -slave -O3 -OPT:alias=typed -OPT:Ofast -W -c -std=c99 -OPT:IEEE_arith=1 slave27.c
mpicc  -O3   *.o -o  benchmark-optimized  