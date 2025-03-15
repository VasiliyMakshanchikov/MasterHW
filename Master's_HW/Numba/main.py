import sys
import time
import math
from numba import njit, prange


@njit(parallel=True, fastmath=True)
def compute_local_sum(steps):
    step_size = 1.0 / steps
    local_sum = 0.0
    
    for i in prange(steps):
        x = (i + 0.5) * step_size
        local_sum += 4.0 / (1.0 + x * x)
    
    return local_sum * step_size


def measure_execution_time(steps, iterations=10):
    start_time = time.time()
    pi_estimate = 0.0
    
    for _ in range(iterations):
        pi_estimate = compute_local_sum(steps)
    
    end_time = time.time()
    return pi_estimate, (end_time - start_time) / iterations


def main():
    TRUE_PI = 3.141592653589793238462643
    
    num_steps = int(sys.argv[1])
    pi_value, avg_time = measure_execution_time(num_steps)
    
    error = abs(pi_value - TRUE_PI)
    print("Difference from true Pi: %.16f" % error)
    print("Computation time per iteration: %.10f sec" % avg_time)


if __name__ == "__main__":
    main()
