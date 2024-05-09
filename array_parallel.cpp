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

vector<int> vecGen(int arraySize) {};

int main()
{
    cout << "Type array size: :" << endl;
    int arraySize;
    cin >> arraySize;

    cout << "What you want to search for: " << endl;
    int missing_number;
    cin >> missing_number;

    vector<int> arr = vecGen(arraySize);

    cout << endl;
    int count = 0;
    for (int i = 0; i < 16; i++)
        if (arr[i] == 3)
            count++;

    cout << count << endl;
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