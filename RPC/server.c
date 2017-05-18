#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.h */

#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#  include <windows.h>
#  include <winsock2.h>
#else
#  include <unistd.h>
#endif

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>

#include <math.h>

#ifdef _WIN32
  #define SLEEP(seconds) SleepEx(seconds * 1000, 1);
#else
  #define SLEEP(seconds) sleep(seconds);
#endif
//=============================================================================//

static xmlrpc_value *
log_b(xmlrpc_env *   const envP,
           xmlrpc_value * const paramArrayP,
           void *         const serverInfo,
           void *         const channelInfo) {

    xmlrpc_double b;
    xmlrpc_double * vector;
    xmlrpc_value * myarray;
    xmlrpc_value * Element;
    int size;

    /* Parse our argument array. */
    xmlrpc_decompose_value(envP, paramArrayP, "(Ad)", &myarray, &b);
    if (envP->fault_occurred)
        return NULL;

    size = xmlrpc_array_size(envP,myarray);

    /* Alocate an operable vector*/
    vector = (xmlrpc_double *) malloc(size*sizeof(double));

    /* Fill our operable vector */
    for (int i=0; i<size; i++){
    	xmlrpc_array_read_item(envP, myarray, i, &Element);
    	xmlrpc_read_double(envP, Element, &vector[i]);
    }


    for (int i=0; i<size; i++){
    	vector[i] = log(vector[i])/log(b);
    	printf("%F",vector[i]);
    }

    //myarray = (xmlrpc_value *) vector;

    /* Return our result. */
    return xmlrpc_build_value(envP, "A", myarray);
}
//=============================================================================//

int 
main(int           const argc, 
     const char ** const argv) {

    struct xmlrpc_method_info3 const methodInfo = {
        /* .methodName     = */ "log_b",
        /* .methodFunction = */ &log_b,
    };
    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_registry * registryP;
    xmlrpc_env env;

    if (argc-1 != 1) {
        fprintf(stderr, "You must specify 1 argument:  The TCP port "
                "number on which the server will accept connections "
                "for RPCs (8080 is a common choice).  "
                "You specified %d arguments.\n",  argc-1);
        exit(1);
    }
    
    xmlrpc_env_init(&env);

    registryP = xmlrpc_registry_new(&env);
    if (env.fault_occurred) {
        printf("xmlrpc_registry_new() failed.  %s\n", env.fault_string);
        exit(1);
    }

    xmlrpc_registry_add_method3(&env, registryP, &methodInfo);
    if (env.fault_occurred) {
        printf("xmlrpc_registry_add_method3() failed.  %s\n",
               env.fault_string);
        exit(1);
    }

    serverparm.config_file_name = NULL;   /* Select the modern normal API */
    serverparm.registryP        = registryP;
    serverparm.port_number      = atoi(argv[1]);
    serverparm.log_file_name    = "/tmp/xmlrpc_log";

    printf("Running XML-RPC server...\n");

    xmlrpc_server_abyss(&env, &serverparm, XMLRPC_APSIZE(log_file_name));
    if (env.fault_occurred) {
        printf("xmlrpc_server_abyss() failed.  %s\n", env.fault_string);
        exit(1);
    }
    /* xmlrpc_server_abyss() never returns unless it fails */

    return 0;
}
