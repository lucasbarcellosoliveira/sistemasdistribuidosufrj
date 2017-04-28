#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

bool run, term=false;

void sigint_handler(int signal){
	cout<<"I received a SIGINT signal!"<<endl; //declares handler for SIGINT signal
	run=false; //allows indefinite 'while' to end
}

void sigabrt_handler(int signal){
	cout<<"I received a SIGABRT signal!"<<endl; //declares handler for SIGABRT signal
	run=false; //allows indefinite 'while' to end
}

void sigterm_handler(int signal){ //declares handler for SIGTERM signals
	cout<<"I received a SIGTERM signal!"<<endl;
	run=false; //allows indefinite 'while' to end
	term=true;
}

int main(){
	cout<<"Receiver started."<<endl;
	cout<<"My id is: "<<getpid()<<endl; //prints process id to be inserted in sender
	cout<<"Busy wait (0) or blocking wait (1)?"<<endl;
	bool block;
	cin>>block;
	signal(SIGINT,sigint_handler); //binds handler to signal
	signal(SIGABRT,sigabrt_handler);
	signal(SIGTERM,sigterm_handler);
	for(int i=0;i<1000;i++){
		if (block){
			cout<<"Awaiting orders..."<<endl;
			run=true;
			while (run); //keeps cycling until handler is called, if blocking waiting
		}
		usleep(2000000); //waits 2 seconds before printing each number to assure readability
		cout<<i<<endl; //placeholder to other commands
		if (term)
			break; //if SIGTERM is received, term==true and loop is broken
	}
	cout<<"Receiver terminated."<<endl;
	return 0;
}

