#include <iostream>
#include <pthread.h>
using namespace std;

#define th_num 4
const int array_size = 16;
int count = 0;
int myarray[array_size] = {2, 3, 0, 2, 3, 3, 1, 0, 0, 1, 3, 2, 2, 3, 1, 0};
int portion = array_size / th_num;

pthread_mutex_t mutex;

struct ThreadData
{
    int id;
    int local_count;
};

void *count3s(void *tid)
{
    int local_counter = 0;
    int id = *(int *)tid;
    int start = id * portion;

    for (int i = start; i < start + portion; i++)
    {
        if (myarray[i] == 3)
        {
            local_counter++;
        }
    }
    pthread_mutex_lock(&mutex);
    count += local_counter;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t threads[th_num];
    pthread_mutex_init(&mutex, NULL);
    ThreadData thread_data[th_num];
    for (int i = 0; i < th_num; i++)
    {
        thread_data[i].id = i;
        pthread_create(&threads[i], NULL, count3s, &thread_data[i]);
    }
    for (int i = 0; i < th_num; i++)
        pthread_join(threads[i], NULL);
    pthread_mutex_destroy(&mutex);

    cout << "3's are = " << count << endl;
}