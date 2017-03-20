#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

#define PORTNUMBER 777
#define BUFFERSIZE 8

using namespace std;

int main(){
	cout<<"Hello! I'm server!"<<endl;
	int socketfd=socket(AF_INET,SOCK_STREAM,0); //declares and initializes socket file descriptor
	struct sockaddr_in server, client; //declares structs that will describe addresses
	server.sin_family=AF_INET; //sets family to mandatory AF_INET
	server.sin_addr.s_addr=0; //INADDR_ANY sets server's address to any
	cout<<"My IP adress is: "<<server.sin_addr.s_addr<<endl;
	server.sin_port=PORTNUMBER; //sets server's port to defined portnumber
	cout<<"Use port: "<<server.sin_port<<endl;
	bind(socketfd, (struct sockaddr*)&server, sizeof(server)); //binds socket referred in file descriptor socketfd to server's adress
	cout<<"Socket ready."<<endl;
	listen(socketfd, 1); //sets maximum number of conecctions to 1
	cout<<"Waiting for connection..."<<endl;
	accept(socketfd, (struct sockaddr*)&client, (socklen_t*)sizeof(client)); //blocking wait until client asks for connection
	cout<<"Connected!"<<endl;
	char snumber[BUFFERSIZE];
	while(!read(socketfd,snumber,BUFFERSIZE)); //blocking wait until successfully receives a char snumber
	int checknumber=stoi(snumber); //converts to int checknumber
	cout<<"I received from client: "<<checknumber<<endl;
	while (checknumber>0){ //until server receives number 0 from client
		while(!read(socketfd,snumber,BUFFERSIZE)); //blocking wait until next number is received
		checknumber=stoi(snumber); //converts new number from char to int
		cout<<"I received from client: "<<checknumber<<endl;
	}
	return 0;
}
