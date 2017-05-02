#include <xmlrpc.h>
#include <xmlrpc_server.h>
#include <xmlrpc_server_abyss.h>

static xmlrpc_value *
sample_add(xmlrpc_env *   const envP,
           xmlrpc_value * const paramArrayP, 
           void *         const serverContext) {

    xmlrpc_int32 x, y, z;

    /* Parse our argument array. */
    xmlrpc_parse_value(envP, paramArrayP, "(ii)", &x, &y);
    if (envP->fault_occurred)
        return NULL;

    /* Add our two numbers. */
    z = x + y;

    /* Return our result. */
    return xmlrpc_build_value(envP, "i", z);
}



int 
main (int           const argc, 
      const char ** const argv) {

    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_registry * registryP;
    xmlrpc_env env;

    xmlrpc_env_init(&env);

    registryP = xmlrpc_registry_new(&env);

    xmlrpc_registry_add_method(
        &env, registryP, NULL, "sample.add", &sample_add, NULL);

    serverparm.config_file_name = argv[1];
    serverparm.registryP = registryP;

    printf("Starting XML-RPC server...\n");

    xmlrpc_server_abyss(&env, &serverparm, XMLRPC_APSIZE(registryP));

    return 0;
}
