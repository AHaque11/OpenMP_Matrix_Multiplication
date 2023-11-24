# OpenMP_Matrix_Multiplication

This C program utilizes OpenMP for parallelization of matrix multiplication. The input is two 2048x2048 matrices. The scheduling type and number of threads are entered by the user through enviroment variables OMP_SCHEDULE and OMP_NUM_THREADS. The default scheduling type is set to "static" and the default number of threads is 1. 

The purpose of the program is to compare the execution time using different scheduling types and numbers of threads, so each matrix was initialized with constant values. The omp_get_wtime function is used to calculate and print the execution time. Matrix multiplication is performed in parallel using OpenMP, and the result is stored in the "result.txt" file.


Example of compilation where the user selects dynamic scheduling with 16 threads:

              gcc -o matrix_multiply matrix_multiply.c
              export OMP_SCHEDULE="dynamic"
              export OMP_NUM_THREADS=16
              ./matrix_multiply


