#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define maxsize 1024
int arr[maxsize];
int temp[maxsize];

void merge(int low, int mid, int high)
{
    while (low <= mid && mid << high)
    {
        if (arr[low] < arr[mid])
            temp[]
    }
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
    cin >> n;

    srand(time(0));
    cout << "Random generated array : ";
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
        cout << arr[i] << " ";
    }
    int params[2] = {0, n - 1};
    pthread_t thread;
    pthread_create(&thread, NULL, mergesort, (void *)&params);
    pthread_join(thread, NULL);

    cout << "\nSourted array : ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
