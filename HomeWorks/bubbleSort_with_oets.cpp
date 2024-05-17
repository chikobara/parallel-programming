#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <time.h>

#define maxSize 1024

int arr[maxSize];
int n, tmp;
int max_threads = (n + 1) / 2;
pthread_mutex_t mutex;

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
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void *compare(void *arg)
{
	int i = tmp;
	tmp += 2;

	if ((i + 1 < n) && (arr[i] > arr[i + 1]))
	{
		swap(&arr[i], &arr[i + 1]);
	}
	return NULL;
}
void oddEven()
{
	pthread_t threads[max_threads];
	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 1)
		{
			tmp = 0;
			for (int j = 0; j < max_threads; j++)
			{
				pthread_create(&threads[j], NULL, compare, NULL);
			}
			for (int j = 0; j < max_threads; j++)
			{
				pthread_join(threads[j], NULL);
			}
		}
		else
		{
			tmp = 1;
			for (int j = 0; j < max_threads; j++)
			{
				pthread_create(&threads[j], NULL, compare, NULL);
			}
			for (int j = 0; j < max_threads; j++)
			{
				pthread_join(threads[j], NULL);
			}
		}
	}
}

void printArray()
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
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
		// printf("%d ", arr[i]);
	}
	printf("\n");

	clock_t start_timer, end_timer;
	start_timer = clock();
	bubbleSort();
	end_timer = clock();
	double timer = ((double)end_timer - start_timer) / CLOCKS_PER_SEC;

	printf("Sorted array : ");
	// printArray();
	printf("\nTime takes : %fs \n", timer);

	printf("Now with OETS sort\n");
	// re-randomize the array
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 10;
		// printf("%d ", arr[i]);
	}
	// printf("\n");

	start_timer = clock();
	oddEven();
	end_timer = clock();
	timer = ((double)end_timer - start_timer) / CLOCKS_PER_SEC;
	// printArray();
	printf("Time taken : %fs \n", timer);

	return 0;
}