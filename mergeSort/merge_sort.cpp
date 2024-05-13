#include <iostream>
#include <vector>
#include <pthread.h>

// Struct for passing parameters to threads
struct ThreadArgs
{
    std::vector<int> &arr;
    int left;
    int right;
};

// Function to merge two sorted arrays
void merge(std::vector<int> &arr, int left, int mid, int right)
{
    std::vector<int> temp;
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];
    for (i = left; i <= right; i++)
        arr[i] = temp[i - left];
}

// Function for merge sort
void *mergeSort(void *args)
{
    ThreadArgs *targs = (ThreadArgs *)args;
    int left = targs->left;
    int right = targs->right;
    std::vector<int> &arr = targs->arr;

    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Create threads for left and right halves
        pthread_t left_thread, right_thread;

        ThreadArgs left_args = {arr, left, mid};
        ThreadArgs right_args = {arr, mid + 1, right};

        pthread_create(&left_thread, NULL, mergeSort, (void *)&left_args);
        pthread_create(&right_thread, NULL, mergeSort, (void *)&right_args);

        // Wait for the threads to finish
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }

    pthread_exit(NULL);
}

int main()
{
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int arr_size = arr.size();

    std::cout << "Given array is \n";
    for (int i = 0; i < arr_size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    // Create arguments for the initial thread
    ThreadArgs args = {arr, 0, arr_size - 1};

    // Create the initial thread for merge sort
    pthread_t initial_thread;
    pthread_create(&initial_thread, NULL, mergeSort, (void *)&args);

    // Wait for the initial thread to finish
    pthread_join(initial_thread, NULL);

    std::cout << "Sorted array is \n";
    for (int i = 0; i < arr_size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}
