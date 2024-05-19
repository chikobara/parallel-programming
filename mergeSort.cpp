#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <time.h>

using namespace std;

#define maxsize 1024
int arr[maxsize];
int temp[maxsize];

void merge(int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
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
void *mergesort(void *args)
{
    int *params = (int *)args;
    int first = params[0];
    int last = params[1];

    if (first < last)
    {
        int mid = first + (last - first) / 2;
        int leftparams[2] = {first, mid};
        int rightparams[2] = {mid + 1, last};

        pthread_t lthread, rthread;

        pthread_create(&lthread, NULL, mergesort, (void *)&leftparams);
        pthread_create(&rthread, NULL, mergesort, (void *)&rightparams);

        pthread_join(lthread, NULL);
        pthread_join(rthread, NULL);

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
    srand(time(0));
    cout << "Random generated elements: ";
    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }
    cout << endl;

    clock_t start_timer, end_timer;

    int params[2] = {0, n - 1};

    pthread_t thread;

    start_timer = clock();
    pthread_create(&thread, NULL, mergesort, (void *)&params);
    pthread_join(thread, NULL);
    end_timer = clock();

    double timer = ((double)end_timer - start_timer) / CLOCKS_PER_SEC; // calculate time taken

    cout << "\nSourted array : ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\nTime taken : " << timer << "s " << endl;
    return 0;
}
