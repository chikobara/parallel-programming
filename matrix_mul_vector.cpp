#include <pthread.h>
#include <iostream>

const int matrix_size = 10;
const int vector_size = 10;

int matrix[matrix_size][matrix_size] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
};

int vector[vector_size] = {2, 4, 3, 5, 7, 3, 5, 7, 8, 3};
int result_vec[vector_size] = {0};

void *multiplyRow(void *thid)
{
    int row = (int)thid;
    int fi = row * 2;
    int li = row * 2 + 2 - 1;
    for (row = fi; row <= li; row++)
    {
        for (int j = 0; j < vector_size; j++)
        {
            result_vec[row] += matrix[row][j] * vector[j];
        }
    }
    pthread_exit(NULL);
    return NULL;
}

int main()
{
    const int threads_num = vector_size / 5;
    pthread_t threads[threads_num];

    for (int i = 0; i < threads_num; i++)
    {
        pthread_create(&threads[i], NULL, multiplyRow, (void *)i);
    }

    for (int i = 0; i < threads_num; i++)
    {
        pthread_join(threads[i], NULL);
    }

    std::cout << "Result vector : " << std::endl;

    for (int i = 0; i < vector_size; i++)
    {
        std::cout << result_vec[i] << " ";
    }

    std::cout << std::endl;
}