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
int arraySize;
int missing_number;
int count = 0;
vector<int> arr;

struct ThreadData
{
    int id;
    int local_counter;
};

void *threadCountMissing(void *thd)
{
    ThreadData *threadData = (ThreadData *)thd;
    int portion = arraySize / th_num;
    int start = threadData->id * portion;
    threadData->local_counter = 0;

    for (int i = start; i < start + portion; i++)
    {
        if (arr[i] == missing_number)
            threadData->local_counter++;
    }
    pthread_mutex_lock(&mutex);
    count += threadData->local_counter;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

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
    cin >> arraySize;

    cout << "What you want to search for: " << endl;

    cin >> missing_number;

    arr = vecGen(arraySize);
    // for (int i = 0; i < arraySize; i++)
    // {
    //     cout << arr[i] << " ";
    // }

    cout << endl;
    ThreadData threadData[th_num];
    countMissing(threadData);
    cout << "There are " << count << " \'" << missing_number << "\'" << endl;

    int sCount = 0;
    for (int i = 0; i < arraySize; i++)
        if (arr[i] == missing_number)
            sCount++;
    cout << "There are " << sCount << " " << " \'" << missing_number << "\'" << " with serial coding" << endl;
    return 0;
}
