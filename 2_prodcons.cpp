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
#define Nc 25

sem_t full, empty;    //semaphores declaration
pthread_mutex_t buffer;    //mutex declaration
long *numbers;    //buffer declaration
int M = 0;



bool isPrime(long n){
    /*checks if long n is prime*/

    for (int i = 2; i < sqrt(n) ; i++)
        if (n % i == 0)
            return false;
    return true;
}


void *producer(){
    /*waits empty semaphore > 1 then puts a number in the buffer (with exclusive access)*/
    
    while(M < 10000){

        sem_wait(&empty);    //wait(empty)
        pthread_mutex_lock(&buffer);    //wait(mutex)

        for (int i = 0 ; i < N ; i++)    //scrolls the buffer
            if (numbers[i] == 0){    //if finds an empty buffer position
                numbers[i] = rand()%10000001+1;    //fill this position whith a random number
                break;    //leave loop "for"
            }
        
        pthread_mutex_unlock(&buffer);    //signal(mutex)
        sem_post(&full);    //signal(full)
    }
    sem_post(&empty);
    pthread_exit(NULL);    //exit thread
}


void *consumer(){
    /*waits full semaphore > 1 then pick up a number from the buffer (with exclusive access) to check if it's prime*/
    long data;    //keep consumed value

    while(M < 10000){
        
        sem_wait(&full);    //wait(full)
        pthread_mutex_lock(&buffer);    //wait(mutex)

        for (int i = 0 ; i < N ; i++)    //scrolls the buffer
            if (numbers[i] != 0){    //if finds a full position
                data = numbers[i];    //keep the number found
                numbers[i] = 0;    //empty the buffer position
                M++;    //increases the counter
                break;    //leave loop "for"
            }

        pthread_mutex_unlock(&buffer);    //signal(mutex)
        sem_post(&empty);    //signa(empty)

        if(isPrime(data));    //check if data is prime or consume resource
    }
    sem_post(&full);
    pthread_exit(NULL);    //exit thread
}


int main(){
    /*___________________________________VARIABLES___________________________________*/
    srand (time(NULL)); //seed to measure the execution time
    numbers = new long[N];  //init the buffer
    pthread_mutex_init(&buffer,0);  //init the buffer mutex with 0
    sem_init(&full, 0, 0); //init the semaphore full(second parameter means that it is only visible by this process)
    sem_init(&empty, 0, N); //init the smaphore empty
    pthread_t threads[Np+Nc]; //threads declaration
    int rc; //handle errors on thread creating
    int t;
    /*_______________________________________________________________________________*/
    /*_____________________________FILL BUFFER WITH ZEROS____________________________*/
    for (int i = 0; i < N; i++) //scrolls the buffer
        numbers[i] = 0; //fill all positions with 0
    /*_______________________________________________________________________________*/
    /*________________________CREATE AND EXECUTE MULTITHREADS________________________*/
    clock_t tStart = clock(), tFinish;  //start timer


    for(t = 0 ; t < Np ; t++){ //for each producer
        rc = pthread_create(&threads[t], NULL, producer, NULL); //creates a producer thread
//cout<<"thread produtora "<<t<<" criada com sucesso!"<<endl;
        if (rc){    //handle error on thread creating
            cout << "ERROR; return code from pthread_create() is" << rc << endl;
            exit(-1);
        }
    }

    for(t = Np ; t < Np + Nc ; t++){ //for each consumer
        rc = pthread_create(&threads[t], NULL, consumer, NULL); //create a consumer thread
//cout<<"thread consumidora "<<t<<" criada com sucesso!"<<endl;
        if (rc){    //handle error on thread creating
            cout << "ERROR; return code from pthread_create() is" << rc << endl;
            exit(-1);
        }
    }

    for (t = 0 ; t < Np + Nc ; t++)    //blocking wait until threads exit
        pthread_join(threads[t],NULL);


    tFinish = clock();  //stop timer

    sem_destroy(&full); //semaphore destructor
    sem_destroy(&empty);    //semaphore destructor
    pthread_mutex_destroy(&buffer); //mutex destructor
    delete numbers; //frees space taken by buffer in heap

    cout << "Done!" << endl;
    cout << "Execution time: " << (double)(tFinish - tStart)/CLOCKS_PER_SEC << endl;
    pthread_exit(NULL); //exit last thread
    /*_______________________________________________________________________________*/
}
