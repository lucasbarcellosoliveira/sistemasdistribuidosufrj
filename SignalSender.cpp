#include <iostream>
#include <csignal>
#include <sys/types.h>

using namespace std;

int main(){
	cout<<"Sender started."<<endl;
	cout<<"Insert receiver id:"<<endl;
	int id;
	cin>>id; //stores id of receiver process, which can be obtained from process manager
	while(true){
		cout<<"Would you like to send SIGINT (1), SIGABRT (2) or SIGTERM (3)? Or quit (4)?"<<endl;
		int sig;
		cin>>sig; //stores signal selection
		if (sig==4)
			break; //allows program to finish
		else
			switch (sig){
				case 1:
					kill (id, SIGINT); //sends SIGINT signal to process
					cout<<"SIGINT signal sent!"<<endl;
					break;
				case 2:
					kill (id, SIGABRT); //sends SIGABRT signal to process
					cout<<"SIGABRT signal sent!"<<endl;
					break;
				case 3:
					kill (id, SIGTERM); //sends SIGTERM signal to process
					cout<<"SIGTERM signal sent!"<<endl;
					break;
			}
	}
	cout<<"Sender terminated."<<endl;
	return 0;
}

