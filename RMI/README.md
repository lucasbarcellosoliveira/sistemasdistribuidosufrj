# RMI Observations

Recommended compilation order: Op -> OpImplementation -> Server -> ServerProcessingThread -> Client

Execute "rmic OpImplementation" and "start rmiregistry" after compiling and before executing Server and Client.

Originally developed in Windows 7.
Tested and approved in Ubuntu and Scientific Linux.

In case more heap space is needed compile as it follows:
java -Xmx4g Client
