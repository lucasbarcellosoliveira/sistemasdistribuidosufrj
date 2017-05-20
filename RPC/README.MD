# Instalation and Compilation Instructions

Before compiling, install XML-RPC dependencies using:
sudo apt-get install libcurl4-gnutls-dev
OR
sudo yum install libcurl-devel.x86_64

Install XML-RPC from source code provided in its official website.

Use the folowing command to compile the .c source files provided using XML-RPC:
/* Client */

gcc client.c -o client -L/usr/local/lib -lxmlrpc_client -lxmlrpc -lxmlrpc_xmlparse -lxmlrpc_xmltok -lxmlrpc_util -lpthread -L/usr/lib/x86_64-linux-gnu -lcurl

/* Server */

gcc server.c -o server -L/usr/local/lib -lxmlrpc_server_abyss -lxmlrpc_server -lxmlrpc_abyss -lxmlrpc -lxmlrpc_xmlparse -lxmlrpc_xmltok -lxmlrpc_util -lpthread -lm
