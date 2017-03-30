//g++ -fpermissive -pthread -w -std=c++11 somador.cpp -o somador
#include <pthread.h>
#include <iostream>
#include <atomic>
#include <time.h>

using namespace std;

#define K 4
#define N 1000000000

atomic_flag lock = ATOMIC_FLAG_INIT;
char* numbers;
int accumulator=0;
int finished = 0;

void acquire(){
    while(lock.test_and_set());
}

void release(){
    lock.clear();
}

void *sum(void* threadid){
    long tid;
    tid = (long)threadid;
    int partial_sum = 0;
    long start = tid*(N/K), end = start+N/K;
    for (long i = start; i < end; i++){
        partial_sum += (int) numbers[i];
        //cout << "valor de i:" << i << endl;
    }

    acquire();
    //cout << "partial_sum is:" << partial_sum << endl;
    accumulator+=partial_sum;
    //cout << "accumulator:" << accumulator << endl;
    finished++;
    release();

    pthread_exit(NULL);
}

int main (int argc, char *argv[]){
    /*___________________________________VARIABLES___________________________________*/
    numbers = new char[N];
    srand (time(NULL));
    pthread_t threads[K];
    int rc;
    long t;
    /*_______________________________________________________________________________*/

    /*_________________________________RANDOM NUMBERS________________________________*/
    cout << "Preparing buffer... It can takes a few seconds" << endl;
    for (int i = 0; i < N; i++)
        numbers[i] = (char*) (rand()%201 - 100);
    cout << "Buffer ready! Let's calculate the problem..." << endl;
    /*_______________________________________________________________________________*/

    /*________________________CREATE AND EXECUTE MULTITHREADS________________________*/
    //start
    clock_t tStart = clock(), tFinish;
    for(t=0; t<K; t++){
        rc = pthread_create(&threads[t], NULL, sum, (void *)t);
        if (rc){
            cout << "ERROR; return code from pthread_create() is" << rc << endl;
            exit(-1);
        }
    }
    while (finished < K);
    tFinish = clock();
    //finished
    cout << "Done!" << endl;
    cout << "Execution time:" << (double)(tFinish - tStart)/CLOCKS_PER_SEC << endl;
    delete numbers;
    pthread_exit(NULL);
    /*_______________________________________________________________________________*/
}
