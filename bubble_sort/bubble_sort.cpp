#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define array_size 10

int arr[array_size] = {9, 6, 9, 4, 2, 7, 6, 5, 0, 1};
int n = array_size;

typedef struct
{
    int start;
    int end;
} thread_args;

void *bubble_sort(void *args)
{
    thread_args *t_args = (thread_args *)args;

    for (int i = t_args->start; i < t_args->end; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[2];
    thread_args t_args[2];

    // split the array into two halves for two threads
    t_args[0].start = 0;
    t_args[0].end = n / 2;
    t_args[1].start = n / 2;
    t_args[1].end = n;

    // create two threads for sorting each half
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&threads[i], NULL, bubble_sort, (void *)&t_args[i]);
    }

    // wait for both threads to finish
    for (int i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
    }
    // merge the sorted halves
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // print the sorted array
    printf("Sorted array : ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
