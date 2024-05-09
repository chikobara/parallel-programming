#include<pthread.h>
#include<iostream>
#include <thread>

using namespace std;


const int array_size = 16;
int arr[array_size] = {2, 3, 0, 2, 3, 3, 1, 0, 0, 1, 3, 2, 2, 3, 1, 0};
int count = 0;

#define th_num 4
int portion = array_size/th_num;


void count3s(int arr[]){
    pthread_t threads[th_num];

    for ( int i = 0; i < th_num; i++){
        pthread_create(thread[i], NULL, count3s_thread, (void*)arg )
    }
}

void *count3s_thread( void ){
    for(int i = 0; i < array_size; i++){
        if(arr[i] == 3){
            count++;
        }
    }
}

int main(){

    count3s(arr);
    cout << count << endl ;
}
