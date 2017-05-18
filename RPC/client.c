#include <stdlib.h>
#include <stdio.h>

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#include "config.h"  /* information about this build environment */

#define NAME "Xmlrpc-c Test Client"
#define VERSION "1.0"

#define N 30
//=============================================================================//

static void 
dieIfFaultOccurred (xmlrpc_env * const envP) {
    if (envP->fault_occurred) {
        fprintf(stderr, "ERROR: %s (%d)\n",
                envP->fault_string, envP->fault_code);
        exit(1);
    }
}
//=============================================================================//

int 
main(double           const argc, 
     const char ** const argv) {

    xmlrpc_env env;
    xmlrpc_value * resultP;
    xmlrpc_double log;
    const char * const serverUrl = "http://localhost:8080/RPC2";
    const char * const methodName = "log_b";

    if (argc-1 > 0) {
        fprintf(stderr, "This program has no arguments\n");
        exit(1);
    }

    /* Initialize our error-handling environment. */
    xmlrpc_env_init(&env);

    /* Start up our XML-RPC client library. */
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    dieIfFaultOccurred(&env);

    printf("Making XMLRPC call to server url '%s' method '%s' "
           "to request a log \n", serverUrl, methodName);

    /* Make the remote procedure call */
    resultP = xmlrpc_client_call(&env, serverUrl, methodName,
                                 "(dd)", (xmlrpc_double) 729, (xmlrpc_double) 9);
    dieIfFaultOccurred(&env);
    
    /* Get our log and print it out. */
    xmlrpc_read_double(&env, resultP, &log);
    dieIfFaultOccurred(&env);
    printf("The log is %F\n", log);
    
    /* Dispose of our result value. */
    xmlrpc_DECREF(resultP);

    /* Clean up our error-handling environment. */
    xmlrpc_env_clean(&env);
    
    /* Shutdown our XML-RPC client library. */
    xmlrpc_client_cleanup();

    return 0;
}