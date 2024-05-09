// #include "stdafx.h"
#include <stdio.h>
// #include <proxy>
#include <iostream>
#include <pthread.h>
using namespace std;

#define NUM_THREADS 5
// define : defining a const value

void *PrintHello(void *threadid)
{
    long tid = (long)threadid;
    cout << "Hello World! Thread ID," << tid << " \n";
    pthread_exit(NULL);
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int rc;
    int t;
    for (t = 0; t < NUM_THREADS; t++)
    {
        cout << "main() : creating thread" << t << endl;
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        // pthread_create(array of threads , NULL, PrintHello (what function u want to this thread ), (void *)t  is point to line 10 function)

        if (rc)
        {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
