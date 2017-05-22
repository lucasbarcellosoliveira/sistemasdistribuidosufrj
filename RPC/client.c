#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#define NAME "Xmlrpc-c Test Client"
#define VERSION "1.0"

#define N 10000
#define K 4

//=============================================================================//
static double TimeSpecToSeconds(struct timespec* ts)
{
    return (double)ts->tv_sec + (double)ts->tv_nsec / 1000000000.0;
}

//=============================================================================//
struct args_t{
    xmlrpc_env env;
    xmlrpc_value * result;
    xmlrpc_value * myarray;
    char * serverUrl;
    char * methodName;
};

//=============================================================================//

static void
dieIfFaultOccurred (xmlrpc_env * const envP) {
    if (envP->fault_occurred) {
        fprintf(stderr, "ERROR: %s (%d)\n",
                envP->fault_string, envP->fault_code);
        exit(1);
    }
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
//=============================================================================//

void *
rpcThread(void* arg){
    struct args_t *args = (struct args_t *)malloc(sizeof(struct args_t));
    args = arg;

    if (args->methodName == "logbx" || "sinx" || "powx"){
	    /* Make the remote procedure call of first type functions */
	    args->result = xmlrpc_client_call(&args->env, args->serverUrl, args->methodName,
	                                 "(Ad)", (xmlrpc_value*) args->myarray, (xmlrpc_double) 2);
	}

	else{
	    /* Make the remote procedure call of second type functions */
	    args->result = xmlrpc_client_call(&args->env, args->serverUrl, args->methodName,
	                                  "(A)", (xmlrpc_value*) args->myarray);//, (xmlrpc_double) 50);
	}
}
//=============================================================================//

int 
main(double           const argc, 
     const char ** const argv) {

	clock_t startc, endc;
	struct timespec startm, endm;
	double elapsedSecondsM, elapsedSecondsC;
    pthread_t threads[K];
    xmlrpc_value * Element;
    xmlrpc_env env;
    xmlrpc_value * item;
    xmlrpc_value * log;
    xmlrpc_double var;
    double number;
    srand(time(NULL));
    char * serverUrl = "http://localhost:8080/RPC2";
    char * methodName = "powx";
    struct args_t args[K];
    int i, k;

    if (argc-1 > 0) {
        fprintf(stderr, "This program has no arguments\n");
        exit(1);
    }

    /* Initialize our error-handling environment. */
    xmlrpc_env_init(&env);

    /* Start up our XML-RPC client library. */
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    dieIfFaultOccurred(&env);

    printf("Making XMLRPC call to server url '%s' method '%s' \n"
           , serverUrl, methodName);

    /* Create random vector */    
    for (i=0; i<K; i++){
        args[i].myarray = xmlrpc_array_new(&env);
        for (k=0; k<N/K; k++){
            number = fRand(0,100);
            item = xmlrpc_double_new(&env, number);
            xmlrpc_array_append_item(&env, args[i].myarray, item);
            xmlrpc_DECREF(item);
        }
        args[i].env = env;
        args[i].serverUrl = serverUrl;
        args[i].methodName = methodName;
    }


//START CLOCK   
    clock_gettime(CLOCK_MONOTONIC, &startm);
    startc = clock();    
//START CLOCK
    for (i=0; i<K; i++){
        pthread_create(&threads[i], NULL, rpcThread, &args[i]);
    }

    for (i=0; i<K; i++){
        pthread_join(threads[i], NULL);
    }

    // for (i=0; i<K; i++){
    // 	for (k=0; k<N/K; k++){
	   //  	xmlrpc_array_read_item(&env, args[i].result, k, &Element);
	   //      xmlrpc_read_double(&env, Element, &var);
	   //      printf("%F\n", var);
    // 	}
    // }
//END CLOCK
    clock_gettime(CLOCK_MONOTONIC, &endm);
    endc = clock();
//END CLOCK

    elapsedSecondsC = (double)(endc - startc)/CLOCKS_PER_SEC;
    elapsedSecondsM = TimeSpecToSeconds(&endm) - TimeSpecToSeconds(&startm);
    printf("Time elapsed by MONOTONIC: %F\n", elapsedSecondsM);
    printf("Time elapsed by CLOCK: %F\n", elapsedSecondsC);


    dieIfFaultOccurred(&env);
    
    /* Get out first type functions */
    // for (i=0; i<10; i++){
    //     xmlrpc_array_read_item(&env, result, i, &log);
    //     xmlrpc_read_double(&env, log, &var);
    //     dieIfFaultOccurred(&env);
    //     printf("%F\n", var);
    // }

    /* Get out second type functions */
    // xmlrpc_read_double(&env, result, &var);
    // printf("%F\n",var);

    /* Dispose of our result value. */
    //for (i=0; i<K; i++)
    //    xmlrpc_DECREF(args[i].result);

    /* Clean up our error-handling environment. */
    xmlrpc_env_clean(&env);
    
    /* Shutdown our XML-RPC client library. */
    xmlrpc_client_cleanup();

    return 0;
}
