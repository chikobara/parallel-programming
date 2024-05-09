#include <pthread.h>
#include <iostream>

// #define HAVE_STRUCT_TIMESPEC

// int r = 0;
int mails = 0;
pthread_mutex_t mutex;
void *PrintHello(void *threadid)
{
	for (int r = 0; r < 10000000; r++)
	{

		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return 0;
}

int main()
{
	if (pthread_mutex_init(&mutex, NULL))
	{
		printf("Unable to initialize a mutex\n");
		return -1;
	}

	pthread_t t1, t2, t3, t4;

	pthread_create(&t1, NULL, PrintHello, NULL);
	pthread_create(&t2, NULL, PrintHello, NULL);
	pthread_create(&t3, NULL, PrintHello, NULL);
	pthread_create(&t4, NULL, PrintHello, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	std::cout << mails << std::endl;

	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
	return 0;
}

////#include "stdafx.h"
// #include <pthread.h>
// #include <stdio.h>
// #include <iostream>
// #include <proxy/proxy.h>
// using namespace std;
// #define NUM_THREADS 5
// void* PrintHello(void* threadid)
//{
//	cout << "Hello World! Thread ID, \n";
//	return NULL;
// }
//
// int main(int argc, char* argv[])
//{
//	pthread_t threads[NUM_THREADS];
//	int rc;
//	long t;
//	for (t = 0; t < NUM_THREADS; t++) {
//		printf("In main: creating thread %ld\n", t);
//		rc = pthread_create(&threads[t], NULL, PrintHello, (void*)t);
//		if (rc) {
//			printf("ERROR; return code from pthread_create() is %d\n", rc);
//		}
//	}
//	pthread_exit(NULL);
// }
