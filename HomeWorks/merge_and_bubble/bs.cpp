#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>

#define maxSize 100

int arr[maxSize];
int n;
typedef struct
{
	int start;
	int end;
} args;

void *sortThread(void *threadArgs)
{
	args *thA = (args *)threadArgs;

	for (int i = thA->start; i < thA->end; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
	// thread_exit(NULL);
	return NULL;
}
void bubbleSort()
{
	pthread_t threads[2];
	args threadArgs[2];

	threadArgs[0].start = 0;
	threadArgs[0].end = n / 2;
	threadArgs[1].start = 0;
	threadArgs[1].end = n;
	for (int i = 0; i < 2; i++)
	{
		pthread_create(&threads[i], NULL, sortThread, (void *)&threadArgs[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		pthread_join(threads[i], NULL);
	}

	int temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main()
{
	std::cout << "Type array size : ";
	std::cin >> n;
	srand(time(0));
	printf("Array : ");
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 10;
		printf("%d ", arr[i]);
	}
	printf("\n");
	bubbleSort();
	printf("Sorted array : ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}