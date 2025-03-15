#!/bin/bash
#SBATCH --job-name=Task1_Makshanchikov              # Название задачи
#SBATCH --error=cpp-%j.err          # Файл для вывода ошибок
#SBATCH --output=cpp-%j.log         # Файл для вывода результатов
#SBATCH --time=02:00:00              # Максимальное время выполнения
#SBATCH --ntasks=16                  # Количество MPI процессов
#SBATCH --constraint="type_a|type_b"   # Предпочтительный тип узлов
#SBATCH -A proj_1651

module load openmpi/4.1.4
mpicxx main.c -Ofast -march=skylake -o main

steps=10000000
echo "$steps steps"
for processes in 1 2 4 8 16
do
    echo "$processes processes"
    mpirun -bind-to none -np $processes ./main $steps
done

echo "----------------------------------------------------"

steps=100000000
echo "$steps steps"
for processes in 1 2 4 8 16
do
    echo "$processes processes"
    mpirun -bind-to none -np $processes ./main $steps
done

echo "----------------------------------------------------"

steps=100000000
echo "$steps steps"
for processes in 1 2 4 8 16
do
    echo "$processes processes"
    mpirun -bind-to none -np $processes ./main $steps
done

