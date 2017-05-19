#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#define NAME "Xmlrpc-c Test Client"
#define VERSION "1.0"

#define N 10
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

int 
main(double           const argc, 
     const char ** const argv) {

    xmlrpc_env env;
    xmlrpc_value * result;
    xmlrpc_value * myarray;
    xmlrpc_value * item;
    xmlrpc_value * log;
    xmlrpc_double var;
    double number;
    srand(time(NULL));
    const char * const serverUrl = "http://localhost:8080/RPC2";
    const char * const methodName = "prodx";

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
    myarray = xmlrpc_array_new(&env);
    
    for (int i=0; i<N; i++){
        number = fRand(0,100);
        item = xmlrpc_double_new(&env, number);
        xmlrpc_array_append_item(&env, myarray, item);
        xmlrpc_DECREF(item);
    }

    /* Make the remote procedure call of first type functions */
    // result = xmlrpc_client_call(&env, serverUrl, methodName,
    //                              "(Ad)", (xmlrpc_value*) myarray, (xmlrpc_double) 2);

    /* Make the remote procedure call of second type functions */
    result = xmlrpc_client_call(&env, serverUrl, methodName,
                                  "(A)", (xmlrpc_value*) myarray);//, (xmlrpc_double) 50);

    dieIfFaultOccurred(&env);
    
    /* Get out first type functions */
    // for (int i=0; i<10; i++){
    //     xmlrpc_array_read_item(&env, result, i, &log);
    //     xmlrpc_read_double(&env, log, &var);
    //     dieIfFaultOccurred(&env);
    //     printf("%F\n", var);
    // }

    /* Get out second type functions */
    xmlrpc_read_double(&env, result, &var);
    printf("%F\n",var);

    /* Dispose of our result value. */
    xmlrpc_DECREF(result);

    /* Clean up our error-handling environment. */
    xmlrpc_env_clean(&env);
    
    /* Shutdown our XML-RPC client library. */
    xmlrpc_client_cleanup();

    return 0;
}
