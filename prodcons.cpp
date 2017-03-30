//g++ -fpermissive -pthread -w -std=c++11 somador.cpp -o somador
#include <pthread.h>
#include <iostream>
#include <atomic>
#include <time.h>
#include <mutex>
#include <semaphore.h>
#include <cmath>

using namespace std;

#define N 2
#define Np 1
#define Nc 1

sem_t full, empty;
pthread_mutex_t bufferbusy;
long numbers[N];
int finished = 0;
int M = 0;

bool isPrime(long n){   //checks if a number is prime
    for (int i = 2; i < sqrt(n) ; i++) //verification up to 1. Can be optimized
        if (n % i == 0)
            return false;
    return true;
}

void *producer(){

    while(M<10000){
        sem_wait(&empty);            // WAIT EMPTY
        pthread_mutex_lock(&bufferbusy);

        for (int i = 0 ; i < N ; i++){
            if (numbers[i] == 0){
                numbers[i] = rand()%10000001+1;
                break;
            }       
        }

        pthread_mutex_unlock(&bufferbusy);
        sem_post(&full);         // SIGNAL FULL
    }


    finished++;
    pthread_exit(NULL);
}

void *consumer(){
    long data;
    bool ready;

    while(M<10000){
        sem_wait(&full);             // WAIT FULL
        pthread_mutex_lock(&bufferbusy);

        ready = false;

        for (int i = 0 ; i < N ; i++){
            if (numbers[i] != 0){
                data = numbers[i];
                numbers[i] = 0;
                ready = true;
                M++;
                break;
            }
        }

        pthread_mutex_unlock(&bufferbusy);
        sem_post(&empty);        // SIGNAL EMPTY

        if (ready)
            if(isPrime(data))
                cout << data << " is prime!" << endl;
            else
                cout << data << " is composite!" << endl;
    }


    finished++;
    pthread_exit(NULL);
}

int main (int argc, char *argv[]){
    /*___________________________________VARIABLES___________________________________*/
    srand (time(NULL));
    pthread_mutex_init(&bufferbusy,0);
    sem_init(&full, 0, N); //parameter 0 means that it is only visible by this process
    sem_init(&empty, 0, N); //parameter 0 means that it is only visible by this process
    pthread_t threads[Np+Nc];
    int rc;
    long t;
    /*_______________________________________________________________________________*/

    /*_________________________________RANDOM NUMBERS________________________________*/
    for (int i = 0; i < N; i++)
        numbers[i] = 0;
    /*_______________________________________________________________________________*/

    /*________________________CREATE AND EXECUTE MULTITHREADS________________________*/
    //start
    clock_t tStart = clock(), tFinish;
    for(t=0; t<Np; t++){ //producer's for
        rc = pthread_create(&threads[t], NULL, producer, NULL);
        if (rc){
            cout << "ERROR; return code from pthread_create() is" << rc << endl;
            exit(-1);
        }
    }

    for(t=Np; t<Np+Nc; t++){ //consumer's for
        rc = pthread_create(&threads[t], NULL, consumer, NULL);
        if (rc){
            cout << "ERROR; return code from pthread_create() is" << rc << endl;
            exit(-1);
        }
    }

    while (finished < Np+Nc);
    tFinish = clock();
    //finish

    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&bufferbusy);

    cout << "Done!" << endl;
    cout << "Execution time:" << (double)(tFinish - tStart)/CLOCKS_PER_SEC << endl;
    pthread_exit(NULL);
    /*_______________________________________________________________________________*/
}
