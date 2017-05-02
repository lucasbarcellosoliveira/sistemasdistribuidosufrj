int 
main(int           const argc, 
     const char ** const argv) {

    xmlrpc_env env;
    xmlrpc_value * resultP;
    int sum;
    char * const clientName = "XML-RPC C Test Client";
    char * const clientVersion = "1.0";
    char * const url = "http://localhost:8080/RPC2";
    char * const methodName = "sample.add";

    /* Initialize our error-handling environment. */
    xmlrpc_env_init(&env);

    /* Start up our XML-RPC client library. */
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, clientName, clientVersion, NULL, 0);
    [ handle possible failure of above ]

    /* Make the remote procedure call */
    resultP = xmlrpc_client_call(&env, url, methodName,
                 "(ii)", (xmlrpc_int32) 5, (xmlrpc_int32) 7);
    [ handle possible failure of above ]
    
    /* Print out the sum the server returned */
    xmlrpc_parse_value(&env, resultP, "i", &sum);
    [ handle possible failure of above ]

    printf("The sum  is %d\n", sum);
    
    /* Dispose of our result value. */
    xmlrpc_DECREF(resultP);

    /* Clean up our error-handling environment. */
    xmlrpc_env_clean(&env);
    
    /* Shutdown our XML-RPC client library. */
    xmlrpc_client_cleanup();

    return 0;
}
