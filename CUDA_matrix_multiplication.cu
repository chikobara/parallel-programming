#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

void generateRandomMatrix(int rows, int cols, int *matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i * cols + j] = rand() % 10;
        }
    }
}

void printMatrix(int rows, int cols, int *matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d\t", matrix[i * cols + j]);
        }
        printf("\n");
    }
    // printf("\n");
}

__global__ void matrixMultiplicationGPU(int rowsA, int colsA, int colsB, int *matrixA, int *matrixB, int *result)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if (i < rowsA && j < colsB)
    {
        int sum = 0;
        for (int k = 0; k < colsA; k++)
        {
            sum += matrixA[i * colsA + k] * matrixB[k * colsB + j];
        }
        result[i * colsB + j] = sum;
    }
}

int main()
{

    int rows, cols;
    printf("Type number of rows: ");
    std::cin >> rows;
    printf("Type number of columns: ");
    std::cin >> cols;

    int size = rows * cols;
    size_t bytes = size * sizeof(int);

    // Allocate memory for matrices on CPU
    int *matrixA_CPU = (int *)malloc(bytes);
    int *matrixB_CPU = (int *)malloc(bytes);
    int *result_CPU = (int *)malloc(bytes);

    // Allocate memory for matrices on GPU
    int *matrixA_GPU;
    int *matrixB_GPU;
    int *result_GPU;
    cudaMalloc((void **)&matrixA_GPU, bytes);
    cudaMalloc((void **)&matrixB_GPU, bytes);
    cudaMalloc((void **)&result_GPU, bytes);

    // Generate random matrices
    generateRandomMatrix(rows, cols, matrixA_CPU);
    generateRandomMatrix(rows, cols, matrixB_CPU);

    // Copy matrices from CPU to GPU
    cudaMemcpy(matrixA_GPU, matrixA_CPU, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(matrixB_GPU, matrixB_CPU, bytes, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((cols + threadsPerBlock.x - 1) / threadsPerBlock.x, (rows + threadsPerBlock.y - 1) / threadsPerBlock.y);

    clock_t start_timer, end_timer;

    start_timer = clock();
    matrixMultiplicationGPU<<<numBlocks, threadsPerBlock>>>(rows, cols, cols, matrixA_GPU, matrixB_GPU, result_GPU);
    end_timer = clock();
    double timer = ((double)end_timer - start_timer) / CLOCKS_PER_SEC;

    cudaMemcpy(result_CPU, result_GPU, bytes, cudaMemcpyDeviceToHost);
    printf("\nMatrix Multiplication : \n");
    // printMatrix(rows, cols, result_CPU);
    printf("Time taken : %fs \n", timer);

    // Free memory
    free(matrixA_CPU);
    free(matrixB_CPU);
    free(result_CPU);
    cudaFree(matrixA_GPU);
    cudaFree(matrixB_GPU);
    cudaFree(result_GPU);
}