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

using namespace std;

//Check name fx
//bool checkName (char *);

//Check CC# fx
//bool checkCCnum(char *);
//Check Exp Date fx
//Check Amount fx

int main(int argc, char ** argv)
{
	//Check # arguments

	char buffer[256]; int echolen, received = 0; unsigned int addrlen, serverlen;
	int sock;

	struct sockaddr_in echoserver;	//structure for server address

	//Create the UDP socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
	perror("Failed to create socket"); exit(EXIT_FAILURE);}

cout << "CREATED UDP socket" << endl;

	//Construct the server sockaddr_in structure
	memset(&echoserver, 0, sizeof(echoserver));	//Clear struct
	echoserver.sin_family = AF_INET;		//Internet IP
	echoserver.sin_addr.s_addr = inet_addr(argv[1]);//IP address
	echoserver.sin_port = htons(atoi(argv[2]));	//Server port

cout << "CONSTRUCTED SERVER ADDR_IN" << endl;

//Bind Socket
serverlen = sizeof(echoserver);
if (bind(sock,(struct sockaddr*) &echoserver, serverlen)<0){perror("Failed to bind server socket"); exit(EXIT_FAILURE);}


	//Send the message to the server
	echolen = strlen(argv[3]);
	if (sendto(sock, argv[3], strlen(argv[3]), 0, (struct sockaddr *) &echoserver, sizeof(echoserver)) != echolen){perror("Mismatch in number of sent bytes"); exit(EXIT_FAILURE);}

cout << echoserver.sin_port << endl;
cout << "SENT MESSAGE TO SERVER" << endl;



	//Receive the message back from the server
	addrlen = sizeof(echoserver);
	if((received = recvfrom(sock, buffer, 256, 0, (struct sockaddr *) &echoserver, &addrlen))<0){
	perror("Failed to receive"); exit(EXIT_FAILURE);}

cout << "RECEIVED MESSAGE BACK FROM" <<endl;
	
	buffer[received] = '\0';
	cout << "Message received: " << buffer << endl;

/*	string name;
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

	return 0;
}
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
