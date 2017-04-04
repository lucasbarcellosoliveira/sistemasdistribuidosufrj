//g++ -fpermissive -pthread -w -std=c++11 2_prodcons.cpp -o 2_prodcons
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
#define Nc 8

sem_t full, empty;  //semaphores declaration
pthread_mutex_t bufferbusy, finish; //mutex declaration
long *numbers;    //buffer declaration
int finished = 0;   //flag declaration
int M = 0;  //counter declaration

bool isPrime(long n){
    /*checks if long n is prime*/
    for (int i = 2; i < sqrt(n) ; i++)
        if (n % i == 0)
            return false;
    return true;
}

void *producer(){
    /*waits empty semaphore > 1 then puts a number in the buffer (with exclusive access)*/
    while(Nc>Np || M<10000){
        sem_wait(&empty);   //WAIT EMPTY
        pthread_mutex_lock(&bufferbusy);    //locks bufferbusy mutex to ensure exclusive access

        for (int i = 0 ; i < N ; i++){  //scrolls the buffer
            if (numbers[i] == 0){   //if finds an empty buffer's position
                numbers[i] = rand()%10000001+1; //fit this position with a random number
                break;  //leave the loop
            }       
        }

        pthread_mutex_unlock(&bufferbusy);  //unlock bufferbusy mutex
        sem_post(&full);    //SIGNAL FULL

        if (Nc>=Np && finished>=Nc) //if there are many consumers, wait for all of them to exit first
            break;
    }

    pthread_mutex_lock(&finish);    //locks finish mutex to ensure exclusive access
    finished++; //count finished threads to measure the execution time
    pthread_mutex_unlock(&finish);    //unlock finish mutex

    pthread_exit(NULL); //finish thread
}

void *consumer(){
    /*waits full semaphore > 1 then pick up a number from the buffer (with exclusive access) to check if it's prime*/
    long data;  //store a buffer number

    while(Np>Nc || M<10000){
        sem_wait(&full);    // WAIT FULL
        pthread_mutex_lock(&bufferbusy);    //locks bufferbusy mutex to ensure exclusive access

        for (int i = 0 ; i < N ; i++){  //scrolls the buffer
            if (numbers[i] != 0){   //if finds a fited buffer position
                data = numbers[i];  //save the number placed at this position
                numbers[i] = 0; //clear the buffer position
                M++;    //increases the consume counter
                break;  //leave the loop
            }
        }

        pthread_mutex_unlock(&bufferbusy);  //unlock bufferbusy mutex
        sem_post(&empty);   //SIGNAL EMPTY

        if(isPrime(data)); //checks if data number is prime
            //cout << data << " is prime!" << endl;
        //else
            //cout << data << " is composite!" << endl;

        if (Np>Nc && finished>=Np) //if there are many producers, wait for all of them to exit
            break;
    }

    pthread_mutex_lock(&finish);    //locks finish mutex to ensure exclusive access
    finished++; //count finished threads to measure the execution time
    pthread_mutex_unlock(&finish);    //unlock finish mutex

    pthread_exit(NULL); //finish thread
}

int main (int argc, char *argv[]){
    /*___________________________________VARIABLES___________________________________*/
    srand (time(NULL)); //seed to measure the execution time
    numbers = new long[N];  //init the buffer
    pthread_mutex_init(&bufferbusy,0);  //init the bufferbusy mutex with 0
    pthread_mutex_init(&finish,0);  //init the finish mutex with 0
    sem_init(&full, 0, 0); //init the semaphore full(second parameter means that it is only visible by this process)
    sem_init(&empty, 0, N); //init the smaphore empty
    pthread_t threads[Np+Nc]; //threads declaration
    int rc; //handle errors on thread creating
    int t; //for loop
    /*_______________________________________________________________________________*/

    /*_____________________________FILL BUFFER WITH ZEROS____________________________*/
    for (int i = 0; i < N; i++) //scrolls the buffer
        numbers[i] = 0; //fill all positions with 0
    /*_______________________________________________________________________________*/

    /*________________________CREATE AND EXECUTE MULTITHREADS________________________*/
    clock_t tStart = clock(), tFinish;  //start timer


    for(t=0; t<Np; t++){ //for each producer
        rc = pthread_create(&threads[t], NULL, producer, NULL); //creates a producer thread
        if (rc){    //handle error on thread creating
            cout << "ERROR; return code from pthread_create() is" << rc << endl;
            exit(-1);
        }
    }

    for(t=Np; t<Np+Nc; t++){ //for each consumer
        rc = pthread_create(&threads[t], NULL, consumer, NULL); //create a consumer thread
        if (rc){    //handle error on thread creating
            cout << "ERROR; return code from pthread_create() is" << rc << endl;
            exit(-1);
        }
    }

    while (finished < Np+Nc);   //blocking wait until all threads have finished
    

    tFinish = clock();  //stop timer

    sem_destroy(&full); //semaphore destructor
    sem_destroy(&empty);    //semaphore destructor
    pthread_mutex_destroy(&bufferbusy); //mutex destructor
    pthread_mutex_destroy(&finish); //mutex destructor

    delete numbers; //frees space taken by buffer in heap

    cout << "Done!" << endl;
    cout << "Execution time:" << (double)(tFinish - tStart)/CLOCKS_PER_SEC << endl;
    pthread_exit(NULL); //finish last thread
    /*_______________________________________________________________________________*/
}

