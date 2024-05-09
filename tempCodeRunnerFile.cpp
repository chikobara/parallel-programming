#include <iostream>
#include <pthread.h>
using namespace std;

#define th_num 4
const int array_size = 16;
int count;
int myarray[array_size] = {2, 3, 0, 2, 3, 3, 1, 0, 0, 1, 3, 2, 2, 3, 1, 0};
int portion = array_size / th_num;

void *count3s(void *tid)
{
    int id = (int)tid;
    count = 0;
    int start = id * portion;
    for (int i = start; i < start + portion; i++)
        if (myarray[i] == 3)
            count++;
    return NULL;
}

int main()
{
    pthread_t threads[th_num];
    for (int i = 0; i < th_num; i++)
    {
        pthread_create(&threads[i], NULL, count3s, (void *)i);
    }
    for (int i = 0; i < th_num; i++)
        pthread_join(threads[i], NULL);
    cout << "3's are = " << count << endl;
}