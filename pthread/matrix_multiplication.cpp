#include <pthread.h>
#include <iostream>
#include <vector>

using namespace std;

#define th_num 5
pthread_mutex_t mutex;

typedef struct
{
    int id;
} args;
args thd[th_num];

int count = 0;
const int arraySize = 10;
vector<int> arr1 = {4, 3, 2, 3, 4, 5, 6, 7, 8, 9};
vector<int> arr2 = {3, 5, 7, 8, 3, 2, 5, 7, 8, 2};
// vector<int> arr3;

// int arr1[arraySize] = {5, 2, 2, 3, 5, 6, 7, 8, 9, 10};
// int arr2[arraySize] = {2, 2, 2, 3, 5, 6, 7, 8, 9, 10};

int arr3[arraySize];
int portion = arraySize / th_num;

void *threadMul(void *thd)
{
    args *threadData = (args *)thd;
    int start = portion * threadData->id;
    for (int i = start; i < start + portion; i++)
    {
        // pthread_mutex_lock(&mutex);
        arr3[i] = arr1[i] * arr2[i];
        // pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void matrixMul()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[th_num];
    for (int i = 0; i < th_num; i++)
    {
        thd[i].id = i;
        pthread_create(&threads[i], NULL, threadMul, (void *)&thd[i]);
    }
    for (int i = 0; i < th_num; i++)
    {
        pthread_join(threads[i], NULL);
    }
}
void printarr(vector<int> array)
{
    for (int i = 0; i < arraySize; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}
void printarr(int array[])
{
    for (int i = 0; i < arraySize; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}
int main()
{
    matrixMul();
    printarr(arr1);
    printarr(arr2);
    printarr(arr3);
    return 0;
}