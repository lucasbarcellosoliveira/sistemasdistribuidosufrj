#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unistd.h>

#define PORTNUMBER 777
#define MAXDELTA 10

using namespace std;

int main(){
	cout<<"Hello! I'm client!"<<endl;
	int socketfd=socket(AF_INET, SOCK_STREAM, 0); //declares and initializes socket file descriptor
	struct sockaddr_in server; //declares structs that will describe server's address
	server.sin_family=AF_INET; //sets family to mandatory AF_INET
	server.sin_addr.s_addr=0; //INADDR_ANY sets server's address to any
	cout<<"Reaching IP adress: "<<server.sin_addr.s_addr<<endl;
	server.sin_port=PORTNUMBER; //sets server's port to defined portnumber
	cout<<"Using port: "<<server.sin_port<<endl;
	cout<<"Attempting connection..."<<endl;
	connect(socketfd,(struct sockaddr*)&server,sizeof(server)); //tries to contact server
	cout<<"Connection succeded!"<<endl;
	cout<<"How many number should I generate and send?"<<endl;
	int n; //will store number of tests to be made
	cin>>n;
	cout<<n<<endl;
	int delta=0; //increment that will take place after each iteration
	string snumber;
	srand(time(NULL));
	for (int i=0;i<n;i++){
		delta+=rand()%MAXDELTA+1; //pseudo-randomly picks a number smaller than or equal to MAXDELTA and bigger than or equal to 1
		snumber=to_string(delta); //converts int delta to string snumber
		cout<<"Sending number "<<delta<<endl;
		write(socketfd,snumber.c_str(),sizeof(snumber.c_str())); //sends number to server through socket
	}
	return 0;
}
