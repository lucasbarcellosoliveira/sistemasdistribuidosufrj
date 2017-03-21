#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#define PORTNUMBER 777
#define BUFFERSIZE 8

using namespace std;

int main(){
	cout<<"Hello! I'm server!"<<endl;
	int socketfd=socket(AF_INET,SOCK_STREAM,0); //declares and initializes socket file descriptor
	struct sockaddr_in server, client; //declares structs that will describe addresses
	server.sin_family=AF_INET; //sets family to mandatory AF_INET
	server.sin_addr.s_addr=INADDR_ANY; //INADDR_ANY sets server's address to any
	//inet_aton("192.168.122.1",&server.sin_addr); //stores IP in in_addr struct
	cout<<"My IP adress is: "<<server.sin_addr.s_addr<<endl;
	server.sin_port=htons(PORTNUMBER); //sets server's port to defined portnumber
	cout<<"Use port: "<<server.sin_port<<endl;
	bind(socketfd, (struct sockaddr*)&server, sizeof(server)); //binds socket referred in file descriptor socketfd to server's adress
	cout<<"Socket ready."<<endl;
	listen(socketfd, 1); //sets maximum number of conecctions to 1
	cout<<"Waiting for connection..."<<endl;
	while(accept(socketfd, (struct sockaddr*)&client, (socklen_t*)sizeof(client))); //blocking wait until client asks for connection
	cout<<"Connected!"<<endl;
	char snumber[BUFFERSIZE]; //declares buffer
	//memset(snumber,0,BUFFERSIZE); //used to initialize buffer with zeros
	while (recv(socketfd,snumber,BUFFERSIZE,0)<0); //blocking wait until successfully receives a char snumber
	int checknumber=stoi(snumber); //converts to int checknumber
	cout<<"I received from client: "<<checknumber<<endl;
	while (checknumber>0){ //until server receives number 0 from client
		memset(snumber,0,BUFFERSIZE);
		while(recv(socketfd,snumber,BUFFERSIZE,0)<0); //blocking wait until next number is received
		checknumber=stoi(snumber); //converts new number from char to int
		cout<<"I received from client: "<<checknumber<<endl;
	}
	return 0;
}
