#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

const double PI_TRUE = 3.141592653589793238462643;

void calculate_pi(unsigned long num_steps, double *pi, int rank, int size) {
    double step = 1.0 / (double)num_steps;
    double local_sum = 0.0;
    
    unsigned long start = rank * num_steps / size;
    unsigned long end = (rank + 1) * num_steps / size;
    
    for (unsigned long i = start; i < end; ++i) {
        double x = (i + 0.5) * step;
        local_sum += 4.0 / (1.0 + x * x);
    }
    
    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        *pi = global_sum * step;
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    
    unsigned long num_steps = strtoul(argv[1], NULL, 10);
    const int iterations = 100;
    double pi = 0.0;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();
    
    for (int i = 0; i < iterations; i++) {
        double local_pi = 0.0;
        calculate_pi(num_steps, &local_pi, rank, size);
        
        if (rank == 0) {
            pi = local_pi;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    double end_time = MPI_Wtime();
    double time_per_iteration = (end_time - start_time) / iterations;
    
    if (rank == 0) {
        double error = fabs(pi - PI_TRUE);
        printf("Difference from true Pi: %.16f\n", error);
        printf("Computation time per iteration: %.10f sec\n", time_per_iteration);
    }
    
    MPI_Finalize();
    return EXIT_SUCCESS;
}
