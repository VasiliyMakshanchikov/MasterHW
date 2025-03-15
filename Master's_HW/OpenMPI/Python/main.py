from mpi4py import MPI
import sys
import math

def compute_local_sum(steps, rank, size):
    step_size = 1.0 / steps
    local_sum = 0.0
    
    for i in range(rank, steps, size):
        x = (i + 0.5) * step_size
        local_sum += 4.0 / (1.0 + x * x)
    
    return local_sum * step_size

def measure_execution_time(steps, iterations=10):
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    
    comm.Barrier()
    start_time = MPI.Wtime()
    
    pi_estimate = 0.0
    for _ in range(iterations):
        local_pi = compute_local_sum(steps, rank, size)
        pi_estimate = comm.reduce(local_pi, op=MPI.SUM, root=0)
        comm.Barrier()
    
    end_time = MPI.Wtime()
    
    return pi_estimate, (end_time - start_time) / iterations

def main():
    TRUE_PI = 3.141592653589793238462643
    
    num_steps = int(sys.argv[1])
    pi_value, avg_time = measure_execution_time(num_steps)
    
    if MPI.COMM_WORLD.Get_rank() == 0:
        error = abs(pi_value - TRUE_PI)
        print("Difference from true Pi: %.16f" % error)
        print("Computation time per iteration: %.10f sec" % avg_time)

if __name__ == "__main__":
    main()
