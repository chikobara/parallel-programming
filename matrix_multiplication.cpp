#include <pthread.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace std;

#define th_num 5
#define maxSize 100
pthread_mutex_t mutex;

typedef struct
{
    int id;
} args;
args thd[th_num];

int count = 0, row, column;

int arr1[maxSize][maxSize];
int arr2[maxSize][maxSize];
int arr3[maxSize][maxSize];
int portion;

void *threadMul(void *thd)
{
    if ((portion = row / th_num) < 1)
        portion = 1;
    else
        portion = row / th_num;

    args *threadData = (args *)thd;
    int start = portion * threadData->id;
    for (int i = start; i < start + portion; i++)
    {
        for (int j = 0; j < column; j++)
        {
            for (int k = 0; k < column; k++)
            {
                arr3[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    return NULL;
}

void matrixMul()
{
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
void printarr()
{
    cout << "1st Array" << endl;
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < column; j++)
            cout << arr1[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    cout << "2nd Array" << endl;
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < column; j++)
            cout << arr2[i][j] << " ";
        cout << endl;
    }
    cout << "3rd Array : " << endl;
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < column; j++)
            cout << arr3[i][j] << " ";
        cout << endl;
    }
}
int main()
{
    cout << "Type array row size : ";
    cin >> row;
    cout << "\nType array column size : ";
    cin >> column;
    srand(time(0));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            arr1[i][j] = rand() % 10;
            arr2[i][j] = rand() % 10;
        }
    }
    cout << endl;
    clock_t start_timer, end_timer;

    start_timer = clock();
    matrixMul();
    end_timer = clock();
    double timer = ((double)end_timer - start_timer) / CLOCKS_PER_SEC;

    printf("Time taken : %fs \n", timer);
    // printarr();
}