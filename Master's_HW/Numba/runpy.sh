#!/bin/bash
#SBATCH --job-name=Task1_Makshanchikov              # Название задачи
#SBATCH --error=cpp-%j.err          # Файл для вывода ошибок
#SBATCH --output=cpp-%j.log         # Файл для вывода результатов
#SBATCH --time=02:00:00              # Максимальное время выполнения
#SBATCH --ntasks=1                   # Количество MPI процессов
#SBATCH --nodes=1                    # Требуемое кол-во узлов
#SBATCH --cpus-per-task=16           # Требуемое кол-во CPU
#SBATCH --constraint="type_a|type_b"   # Предпочтительный тип узлов
#SBATCH -A proj_1651

steps=10000000
echo "$steps steps"
for threads in 1 2 4 8 16
do
    echo "$threads threads"
    NUMBA_NUM_THREADS=$threads python main.py $steps
done

echo "----------------------------------------------------"

steps=100000000
echo "$steps steps"
for threads in 1 2 4 8 16
do
    echo "$threads threads"
    NUMBA_NUM_THREADS=$threads python main.py $steps
done

echo "----------------------------------------------------"

steps=1000000000
echo "$steps steps"
for threads in 1 2 4 8 16
do
    echo "$threads threads"
    NUMBA_NUM_THREADS=$threads python main.py $steps
done

echo "----------------------------------------------------"



