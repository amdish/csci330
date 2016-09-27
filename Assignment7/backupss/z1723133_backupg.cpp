/***************
Amol Shah | CSCI330 | Assignment 7 | 04/20/2016
***************/
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cerrno>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

//Check name fx
//bool checkName (char *);
//Check CC# fx
//bool checkCCnum(char *);
//Check Exp Date fx
//Check Amount fx
//string getUserInfo();

int main(int argc, char ** argv)
{
	struct sockaddr_in echoserver;	//structure for server address
	char buffer[256]; 
	int 
		echolen, 
		received = 0; 
		unsigned int addrlen, 
		serverlen,
		sock;
		const char userInput[] = "3715 199624 21012:10/2016:12.40:Jgn";
	
	cout << userInput << endl;

//Create the UDP socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){//Error Checking
		perror("Failed to create socket"); exit(EXIT_FAILURE);}

struct hostent *hp;
char *host = "hopper.cs.niu.edu";
hp = gethostbyname(host);

/*memcpy(&echoserver.sin_addr, hp->h_addr_list[0], hp->h_length);
echoserver.sin_family = AF_INET;
echoserver.sin_port = htons(4445);
*/
/*
//cout << "--" <<hp->h_addr << endl;
paddr((unsigned char*) hp->h_addr_list[1]);
*/
//Construct the server sockaddr_in structure
	memset(&echoserver, 0, sizeof(echoserver));	//Clear struct
	echoserver.sin_family = AF_INET;		//Internet IP	
	echoserver.sin_addr.s_addr = inet_addr("10.158.56.24");
	echoserver.sin_port = htons(4445);		//Server port


//cout << echoserver.sin_addr.s_addr << endl;	
//cout << echoserver.sin_port << endl;

//Send the message to the server
	echolen = strlen(userInput);
	if (sendto(sock, userInput, strlen(userInput), 0, (struct sockaddr *) &echoserver, sizeof(echoserver)) != echolen){perror("Mismatch in number of sent bytes"); exit(EXIT_FAILURE);}

//Receive the message back from the server
	addrlen = sizeof(echoserver);
	if((received = recvfrom(sock, buffer, 256, 0, (struct sockaddr *) &echoserver, &addrlen))<0){
	perror("Failed to receive"); exit(EXIT_FAILURE);}

//Null terminate char array
	buffer[received] = '\0';
//Output Response from server
	cout << "Message received: " << buffer << endl;

	return 0;
}
/*
string getUserInfo(){

        string name;
        char
                name[64],
                CCnum[17];

        cout << "Welcome to the Credit Card transaction verification utility:" << endl;
        cout << "Enter card holder name: ";
        cin.getline(name, 64);
        if (!checkName(name))
        {
                cout << "Name invalid, please re-enter: ";
                cin.getline(name, 64);
        }

        cout << "Enter CC number: ";
        cin.getline(CCnum, 16);
        while (!checkCCnum(CCnum))
        {
                cout << "CC number invalid, please re-enter: ";
                cin.getline(CCnum, 17);
        }
*/

/*
bool checkName (char * inName)
{
	cout << strlen(inName) << endl;	
	return true;
}

bool checkCCnum (char * inCCnum)
{
	cout << strlen(inCCnum) << endl;
	if (strlen(inCCnum) <= 16 && strlen(inCCnum) >= 15)
		return true;
	else
		return false;
}*/
