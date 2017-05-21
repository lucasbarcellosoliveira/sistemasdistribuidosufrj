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
logbx(xmlrpc_env *   const envP,
           xmlrpc_value * const paramArrayP,
           void *         const serverInfo,
           void *         const channelInfo) {

    xmlrpc_double b;
    xmlrpc_double * vector;
    xmlrpc_value * myarray;
    xmlrpc_value * Element;
    xmlrpc_value * item;
    xmlrpc_value * rArray;
    int size, i;

    /* Parse our argument array. */
    xmlrpc_decompose_value(envP, paramArrayP, "(Ad)", &myarray, &b);
    if (envP->fault_occurred)
        return NULL;

    size = xmlrpc_array_size(envP,myarray);

    /* Alocate an operable vector*/
    vector = (xmlrpc_double *) malloc(size*sizeof(double));
    rArray = xmlrpc_array_new(envP);

    /* Fill our operable vector */
    for (i=0; i<size; i++){
    	xmlrpc_array_read_item(envP, myarray, i, &Element);
    	xmlrpc_read_double(envP, Element, &vector[i]);

    	vector[i] = log(vector[i])/log(b);
    	item = xmlrpc_double_new(envP, vector[i]);
    	xmlrpc_array_append_item(envP, rArray, item);
    }

    /* Return our result. */
    return xmlrpc_build_value(envP, "A", rArray);
}
//=============================================================================//

static xmlrpc_value *
sinx(xmlrpc_env *   const envP,
           xmlrpc_value * const paramArrayP,
           void *         const serverInfo,
           void *         const channelInfo) {

    xmlrpc_double * vector;
    xmlrpc_value * myarray;
    xmlrpc_value * Element;
    xmlrpc_value * item;
    xmlrpc_value * rArray;
    int size, i;

    /* Parse our argument array. */
    xmlrpc_decompose_value(envP, paramArrayP, "(A)", &myarray);
    if (envP->fault_occurred)
        return NULL;

    size = xmlrpc_array_size(envP,myarray);

    /* Alocate an operable vector*/
    vector = (xmlrpc_double *) malloc(size*sizeof(double));
    rArray = xmlrpc_array_new(envP);

    /* Fill our operable vector */
    for (i=0; i<size; i++){
    	xmlrpc_array_read_item(envP, myarray, i, &Element);
    	xmlrpc_read_double(envP, Element, &vector[i]);

    	vector[i] = sin(vector[i]);
    	item = xmlrpc_double_new(envP, vector[i]);
    	xmlrpc_array_append_item(envP, rArray, item);
    }

    /* Return our result. */
    return xmlrpc_build_value(envP, "A", rArray);
}
//=============================================================================//

static xmlrpc_value *
powx(xmlrpc_env *   const envP,
           xmlrpc_value * const paramArrayP,
           void *         const serverInfo,
           void *         const channelInfo) {

    xmlrpc_double p;
    xmlrpc_double * vector;
    xmlrpc_value * myarray;
    xmlrpc_value * Element;
    xmlrpc_value * item;
    xmlrpc_value * rArray;
    int size, i;

    /* Parse our argument array. */
    xmlrpc_decompose_value(envP, paramArrayP, "(Ad)", &myarray, &p);
    if (envP->fault_occurred)
        return NULL;

    size = xmlrpc_array_size(envP,myarray);

    /* Alocate an operable vector*/
    vector = (xmlrpc_double *) malloc(size*sizeof(double));
    rArray = xmlrpc_array_new(envP);

    /* Fill our operable vector */
    for (i=0; i<size; i++){
    	xmlrpc_array_read_item(envP, myarray, i, &Element);
    	xmlrpc_read_double(envP, Element, &vector[i]);

    	vector[i] = pow(vector[i],p);
    	item = xmlrpc_double_new(envP, vector[i]);
    	xmlrpc_array_append_item(envP, rArray, item);
    }

    /* Return our result. */
    return xmlrpc_build_value(envP, "A", rArray);
}
//=============================================================================//

static xmlrpc_value *
sumx(xmlrpc_env *   const envP,
           xmlrpc_value * const paramArrayP,
           void *         const serverInfo,
           void *         const channelInfo) {

    xmlrpc_double * vector;
    xmlrpc_value * myarray;
    xmlrpc_value * Element;
    xmlrpc_value * item;
    xmlrpc_double rDouble = 0;
    int size, i;

    /* Parse our argument array. */
    xmlrpc_decompose_value(envP, paramArrayP, "(A)", &myarray);
    if (envP->fault_occurred)
        return NULL;

    size = xmlrpc_array_size(envP,myarray);

    /* Alocate an operable vector*/
    vector = (xmlrpc_double *) malloc(size*sizeof(double));

    /* Fill our operable vector */
    for (i=0; i<size; i++){
    	xmlrpc_array_read_item(envP, myarray, i, &Element);
    	xmlrpc_read_double(envP, Element, &vector[i]);

    	rDouble += vector[i];
    }

    /* Return our result. */
    return xmlrpc_build_value(envP, "d", rDouble);
}
//=============================================================================//

static xmlrpc_value *
largerThanx(xmlrpc_env *   const envP,
           xmlrpc_value * const paramArrayP,
           void *         const serverInfo,
           void *         const channelInfo) {

	xmlrpc_double b;
    xmlrpc_double * vector;
    xmlrpc_value * myarray;
    xmlrpc_value * Element;
    xmlrpc_value * item;
    xmlrpc_double rDouble = 0;
    int size, i;

    /* Parse our argument array. */
    xmlrpc_decompose_value(envP, paramArrayP, "(Ad)", &myarray, &b);
    if (envP->fault_occurred)
        return NULL;

    size = xmlrpc_array_size(envP,myarray);

    /* Alocate an operable vector*/
    vector = (xmlrpc_double *) malloc(size*sizeof(double));

    /* Fill our operable vector */
    for (i=0; i<size; i++){
    	xmlrpc_array_read_item(envP, myarray, i, &Element);
    	xmlrpc_read_double(envP, Element, &vector[i]);

    	if (vector[i]>b)
    		rDouble ++;
    }

    /* Return our result. */
    return xmlrpc_build_value(envP, "d", rDouble);
}
//=============================================================================//

static xmlrpc_value *
prodx(xmlrpc_env *   const envP,
           xmlrpc_value * const paramArrayP,
           void *         const serverInfo,
           void *         const channelInfo) {

    xmlrpc_double * vector;
    xmlrpc_value * myarray;
    xmlrpc_value * Element;
    xmlrpc_value * item;
    xmlrpc_double rDouble = 1;
    int size, i;

    /* Parse our argument array. */
    xmlrpc_decompose_value(envP, paramArrayP, "(A)", &myarray);
    if (envP->fault_occurred)
        return NULL;

    size = xmlrpc_array_size(envP,myarray);

    /* Alocate an operable vector*/
    vector = (xmlrpc_double *) malloc(size*sizeof(double));

    /* Fill our operable vector */
    for (i=0; i<size; i++){
    	xmlrpc_array_read_item(envP, myarray, i, &Element);
    	xmlrpc_read_double(envP, Element, &vector[i]);

    	rDouble *= vector[i];
    }

    /* Return our result. */
    return xmlrpc_build_value(envP, "d", rDouble);
}
//=============================================================================//

int 
main(int           const argc, 
     const char ** const argv) {

    struct xmlrpc_method_info3 const methodInfoLogbx = {
        /* .methodName     = */ "logbx",
        /* .methodFunction = */ &logbx,
    };
    struct xmlrpc_method_info3 const methodInfoSinx = {
        /* .methodName     = */ "sinx",
        /* .methodFunction = */ &sinx,
    };
    struct xmlrpc_method_info3 const methodInfoPowx = {
        /* .methodName     = */ "powx",
        /* .methodFunction = */ &powx,
    };
    struct xmlrpc_method_info3 const methodInfoSumx = {
        /* .methodName     = */ "sumx",
        /* .methodFunction = */ &sumx,
    };
    struct xmlrpc_method_info3 const methodInfoLargerThanx = {
        /* .methodName     = */ "largerThanx",
        /* .methodFunction = */ &largerThanx,
    };
    struct xmlrpc_method_info3 const methodInfoProdx = {
        /* .methodName     = */ "prodx",
        /* .methodFunction = */ &prodx,
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

    xmlrpc_registry_add_method3(&env, registryP, &methodInfoLogbx);
    xmlrpc_registry_add_method3(&env, registryP, &methodInfoSinx);
    xmlrpc_registry_add_method3(&env, registryP, &methodInfoPowx);
    xmlrpc_registry_add_method3(&env, registryP, &methodInfoSumx);
    xmlrpc_registry_add_method3(&env, registryP, &methodInfoLargerThanx);
    xmlrpc_registry_add_method3(&env, registryP, &methodInfoProdx);
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
