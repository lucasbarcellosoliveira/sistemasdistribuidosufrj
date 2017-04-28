#include <iostream>
#include <csignal>

using namespace std;

int main(){
	cout<<"Sender started."<<endl;
	cout<<"Insert receiver id:"<<endl;
	int id;
	cin>>id; //stores id of receiver process, which can be obtained from process manager
	if(kill(id, 0)){ //sends signal 0 (test signal) to check if receiver exists. 'kill' returns 0 if sucessfull
		cout<<"Process does not exist."<<endl;
		return -1;
	}
	else
		cout<<"Destination process found!"<<endl;
	int sig;
	while(true){
		cout<<"Would you like to send SIGINT (1), SIGABRT (2) or SIGTERM (3)? Or quit (4)?"<<endl;
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
			}
	}
	cout<<"Sender terminated."<<endl;
	return 0;
}

