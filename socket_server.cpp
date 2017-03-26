#ifdef _WIN64
#include <winsock.h>
#else
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif
#include <iostream>
#include <cstring>

#define PORTNUMBER 4999
#define BUFFERSIZE 8

using namespace std;

void error(const char *msg) {
    perror(msg);
    exit(1);
}

bool isPrime(int n) { //checks if a number is prime
    for (int i = n - 1; i > 1; i--) //verification up to 1. Can be optimized
        if (n % i == 0)
            return false;
    return true;
}

int main() {

    /*______________________________VARIABLES_________________________________*/
    struct sockaddr_in server, client; //declares structs that will describe addresses
    socklen_t client_size = sizeof (client);
    char snumber[BUFFERSIZE]; //declares buffer
    string response;
    #ifdef _WIN64
    WSADATA wsaData;
    WSAStartup(0x0202, &wsaData);
    #endif
    /*________________________________________________________________________*/


    /*______________________________OPEN SOCKET_______________________________*/
    cout << "Hello! I'm server!" << endl;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0); //declares and initializes socket file descriptor
    if (socketfd < 0)
        error("Erro na instanciacao do socket");
    /*________________________________________________________________________*/


    /*______________________________CONFIG ADDRESS____________________________*/
    server.sin_family = AF_INET; //sets family to mandatory AF_INET
    server.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY sets server's address to any
    server.sin_port = htons(PORTNUMBER); //sets server's port to defined portnumber
    cout << "My IP adress is: " << server.sin_addr.s_addr << endl;
    cout << "Use port: " << PORTNUMBER << endl;
    /*________________________________________________________________________*/


    /*______________________________BIND AND LISTEN___________________________*/
    if (bind(socketfd, (struct sockaddr*) &server, sizeof (server)) < 0)
        error("Erro no bind()"); //binds socket referred in file descriptor socketfd to server's adress
    cout << "Socket ready." << endl;
    listen(socketfd, 1); //sets maximum number of conecctions to 1
    /*________________________________________________________________________*/


    /*______________________________ACCEPT CONNECTION_________________________*/
    cout << "Waiting for connection..." << endl;
    int newsocketfd = accept(socketfd, (struct sockaddr*) &client, &client_size); //blocking wait until client asks for connection
    if (newsocketfd < 0)
        error("Erro no accept()");
    cout << "Connected!" << endl;
    /*________________________________________________________________________*/


    /*______________________________FIRST CLIENT RECEIVE_______________________*/
    memset(snumber, 0, BUFFERSIZE); //used to initialize buffer with zeros
    recv(newsocketfd, snumber, BUFFERSIZE, 0); //blocking wait until successfully receives a char snumber
    int checknumber = stoi(snumber); //converts to int checknumber
    cout << "I received from client: " << checknumber << endl;
    /*________________________________________________________________________*/


    
    while (checknumber != 0) { //until server receives number 0 from client
        /*_____  ___________________SEND TO CLIENT____________________________*/
        if (checknumber == 1) {
            cout << "Telling client that 1 is not prime nor composite..." << endl;
            response = to_string(0); //0 means 'not prime nor composite'
            send(newsocketfd, response.c_str(), sizeof (response), 0); //answers client
        } else
            if (isPrime(checknumber)) { //checks if number is prime
            cout << "Telling client that " << checknumber << " is prime..." << endl;
            response = to_string(1); //1 means 'prime'
            send(newsocketfd, response.c_str(), sizeof (response), 0); //answers client
        } else {
            cout << "Telling client that " << checknumber << " is composite..." << endl;
            response = to_string(2); //2 means 'composite'
            send(newsocketfd, response.c_str(), sizeof (response), 0); //answers client
        }
        /*____________________________________________________________________*/

        /*______________________________RECEIVE FROM CLIENT____________________*/
        memset(snumber, 0, BUFFERSIZE); //used to initialize buffer with zeros
        recv(newsocketfd, snumber, BUFFERSIZE, 0); //blocking wait until next number is received
        checknumber = stoi(snumber); //converts new number from char to int
        cout << "I received from client: " << checknumber << endl;
    }
    /*________________________________________________________________________*/


    /*_____________CLOSE CONNECTION AND TERMINATE THE PROCESS_________________*/
    cout << "Closing socket connection..." << endl;
    #ifdef _WIN64
    closesocket(newsocketfd);
    closesocket(socketfd);
    WSACleanup();
    #else
    close(newsocketfd); //closes both sides of connection, differently form shutdown()
    close(socketfd);
    #endif
    cout << "Connection ended. Bye!" << endl;
    return 0;
    /*________________________________________________________________________*/
}
