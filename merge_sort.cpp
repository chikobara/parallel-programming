#include <iostream>
#include <pthread.h>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

#define MAX_SIZE 1000

using namespace std;

int arr[MAX_SIZE];
int temp[MAX_SIZE];

void merge(int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= high)
        temp[k++] = arr[j++];
    for (i = low; i <= high; i++)
        arr[i] = temp[i];
}

void *mergeSort(void *arg)
{
    int *params = (int *)arg;
    int first = params[0];
    int last = params[1];

    if (first < last)
    {
        int mid = first + (last - first) / 2;

        int leftParams[2] = {first, mid};
        int rightParams[2] = {mid + 1, last};

        pthread_t leftThread, rightThread;

        pthread_create(&leftThread, NULL, mergeSort, (void *)leftParams);
        pthread_create(&rightThread, NULL, mergeSort, (void *)rightParams);

        pthread_join(leftThread, NULL);
        pthread_join(rightThread, NULL);

        merge(first, mid, last);
    }
    pthread_exit(NULL);
    return NULL;
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    // cout << "Enter the elements: ";
    // for (int i = 0; i < n; ++i)
    //     cin >> arr[i];

    srand(time(0));
    cout << "Random generated elements: ";
    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }
    cout << endl;

    int params[2] = {0, n - 1};

    pthread_t sortThread;
    pthread_create(&sortThread, NULL, mergeSort, (void *)params);
    pthread_join(sortThread, NULL);

    cout << "Sorted array: ";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
