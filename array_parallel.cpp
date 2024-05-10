#include <iostream>
#include <vector>
#include <random>

using namespace std;

// initialize random egnine
random_device rd;
default_random_engine engine(rd());
// Define a uniform distribution for numbers between 0 and 9 (inclusive)
uniform_int_distribution<int> distribution(0, 9);
// Generate a random number within the specified range
// int random_number = distribution(engine);

pthread_mutex_t mutex;

#define th_num 5

struct ThreadData
{
    int id;
    int local_counter;
    int arraySize;
    vector<int> arr;
    int missing_number;
};
int count = 0;

void countMissing(ThreadData threadData[])
{
    pthread_mutex_init(&mutex, NULL);

    // creating threads array
    pthread_t threads[th_num];
    for (int i = 0; i < th_num; i++)
    {
        threadData[i].id = i;
        pthread_create(&threads[i], NULL, threadCountMissing, &threadData[i]);
    }
    for (int i = 0; i < th_num; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
}
void *threadCountMissing(void *thd)
{
    ThreadData *threadData = (ThreadData *)thd;
    int portion = threadData->arraySize / th_num;
    int start = threadData->id * portion;

    for (int i = start; i < start + portion; i++)
    {
        if (threadData->arr[i] == threadData->missing_number)
            threadData->local_counter++;
    }
    pthread_mutex_lock(&mutex);
    count += threadData->local_counter;
    pthread_mutex_unlock(&mutex);
    return NULL;
}
vector<int> vecGen(int arraySize)
{
    vector<int> arr(arraySize);
    for (int i = 0; i < arraySize; i++)
    {
        arr[i] = distribution(engine);
    }
    return arr;
}
int main()
{
    cout << "Type array size: :" << endl;
    int arraySize;
    cin >> arraySize;

    cout << "What you want to search for: " << endl;
    int missing_number;
    cin >> missing_number;

    vector<int> arr = vecGen(arraySize);

    ThreadData threadData[th_num];

    cout << endl;

    cout << "There are " << count << " " << missing_number << endl;

    int sCount = 0;
    for (int i = 0; i < arraySize; i++)
        if (arr[i] == missing_number)
            sCount++;
}
