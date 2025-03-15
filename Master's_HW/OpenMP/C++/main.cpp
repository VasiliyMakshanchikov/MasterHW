#include <iostream>
#include <iomanip>
#include <cmath>
#include <omp.h>

const double PI_REF = 3.141592653589793;
const int NUM_ITERATIONS = 100;

// Функция для вычисления числа Pi и измерения времени выполнения
double computePi(unsigned long steps) {
    double step = 1.0 / steps;
    double sum = 0.0;
    
    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (unsigned long i = 0; i < steps; ++i) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    
    return sum * step;
}

// Функция для измерения среднего времени вычисления Pi
double measureComputePiTime(unsigned long steps, double &pi) {
    double totalTime = 0.0;
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        double start = omp_get_wtime();
        pi = computePi(steps);
        double end = omp_get_wtime();
        totalTime += (end - start);
    }
    return totalTime / NUM_ITERATIONS; // Среднее время выполнения
}

int main(int argc, char** argv) {
    unsigned long steps = std::stoul(argv[1]);
    double pi = 0.0;
    double avgTime = measureComputePiTime(steps, pi);
    double error = std::fabs(pi - PI_REF);
    
    std::cout << "Ошибка: " << std::fixed << std::setprecision(16) << error << std::endl;
    std::cout << "Среднее время выполнения: " << std::fixed << std::setprecision(10) << avgTime << " с" << std::endl;
    
    return 0;
}
