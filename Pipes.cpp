#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>

#define MAXDELTA 10
#define BUFFERSIZE 8

using namespace std;

bool isPrime(int n){ //checks if a number is prime
	for (int i=n-1;i>1;i--) //verification up to 1. Can be optimized
		if (n%i==0)
			return false;
	return true;
}

int main(){
	int delta; //increment that will be made after each iteration
	cout<<"Producer started."<<endl;
	cout<<"How many numbers shall I generate, my good sir?"<<endl;
	int ent; //stores the number of tests that will be generated and sent
	cin>>ent;
	srand(time(NULL));
	int id, pipeline[2]; //pipeline will be used in anonymous/unnamed pipe
	pipe(pipeline); //pipeline[0] will be used for reading and pipeline[1] will be used for writing
	id=fork(); //child process created. Hereinafter, code is being executed by both process
	if (id>0){ //checks if process executing this line is the parent process
		close(pipeline[0]); //reading-end won't be used by parent process
		string snumber;
		for(int i=0;i<ent;i++){
			delta+=rand()%MAXDELTA+1; //pseudo-randomly picks a number smaller than or equal to MAXDELTA and bigger than or equal to 1
			cout<<"Parent: "<<delta<<endl;
			snumber=to_string(delta);
			write(pipeline[1], snumber.c_str(), sizeof(snumber.c_str())); //writes number. 'snumber' is converted to const type. Size is acquired based on it
		}
		cout<<"Parent: 0"<<endl;
		snumber=to_string(0);
		write(pipeline[1], snumber.c_str(), sizeof(snumber.c_str())); //writes 0. 'snumber' is converted to const type. Size is acquired based on it
		close(pipeline[1]); //closes pipe's remaining end after use
		exit(0); //finished process. Equivalent to exit(EXIT_SUCCESS)
	}
	else
		if (id==0){ //checks if process executing this line is child process
			close(pipeline[1]); //closes pipeline's writing-end
			char snumber[BUFFERSIZE]; //creates reading buffer
			read(pipeline[0], snumber, BUFFERSIZE); //reads from pipeline
			int n=stoi(snumber); //converts string read from pipe to an int
			cout<<"Child: "<<n<<endl;
			while(n>0){
				if (n==1)
					cout<<"Child: 1 is not prime nor composite."<<endl;
				else
					if (isPrime(n)) //checks if number is prime
						cout<<"Child: "<<n<<" is prime."<<endl;
					else
						cout<<"Child: "<<n<<" is composite."<<endl;
				read(pipeline[0], snumber, BUFFERSIZE); //reads from pipeline
				n=stoi(snumber); //converts string read from pipe to an int
				cout<<"Child: "<<n<<endl;
			}
			close(pipeline[0]); //closes pipe's remaining end after use
			exit(0); //finished process. Equivalent to exit(EXIT_SUCESS)
		}
		else //if id<0, fork failed
			cout<<"Failed to create child process."<<endl;
	return 0;

}
