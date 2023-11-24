#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 2048

int main() {
    int i, j, k;
    double start_time, end_time;

    // Dynamic memory allocation for matrices A, B, and result
    int** A = (int**)malloc(SIZE * sizeof(int*));
    int** B = (int**)malloc(SIZE * sizeof(int*));
    int** result = (int**)malloc(SIZE * sizeof(int*));

    for (i = 0; i < SIZE; i++) {
        A[i] = (int*)malloc(SIZE * sizeof(int));
        B[i] = (int*)malloc(SIZE * sizeof(int));
        result[i] = (int*)malloc(SIZE * sizeof(int));
    }

    // Set environment variables for number of threads and scheduling type
    char* num_threads_input = getenv("OMP_NUM_THREADS");
    char* schedule = getenv("OMP_SCHEDULE");

    int num_threads = num_threads_input ? atoi(num_threads_input) : 1;

    if (schedule == NULL) {
        schedule = "static"; // Default scheduling
    }

    omp_set_num_threads(num_threads);

    // Initialize matrices A and B
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            A[i][j] = 1;
            B[i][j] = 2;
        }
    }

    // Matrix multiplication, start timing
    start_time = omp_get_wtime();

    #pragma omp parallel for shared(A, B, result) private(i, j, k) schedule(runtime)
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (k = 0; k < SIZE; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end_time = omp_get_wtime();

    // Save result matrix to result.txt
    FILE* fp;
    fp = fopen("result.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            fprintf(fp, "%d ", result[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    // Calculate and print execution time
    printf("Execution time: %f seconds\n", end_time - start_time);
    

    // Free allocated memory
    for (i = 0; i < SIZE; i++) {
        free(A[i]);
        free(B[i]);
        free(result[i]);
    }
    free(A);
    free(B);
    free(result);

    return 0;
}






