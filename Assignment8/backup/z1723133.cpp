//Amol Shah | Assignment 8 | CS330 | 05/03/16

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
#include <sys/uio.h>
#include <dirent.h>
using namespace std;

int main (int argc, char ** argv)
{
	//Check for correct arguments
	if (argc < 2)
		cout << "Incorrect Arguments\n";

	int 	sock,		//Socket file descriptor 
		received,
		echolen;

	unsigned int 	addrlen, 
			serverlen,
			clientlen;

	struct sockaddr_in 	echoserver, 
				echoclient;	//Structer for server address
	char buffer[256]; 	

//Create the TCP socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//Error Checking
	perror("Failed to create socket");
	exit (EXIT_FAILURE);
}
//Construct the server sockaddr_in structure
	memset(&echoserver, 0, sizeof(echoserver));	//Clear struct
	echoserver.sin_family = AF_INET;		//Internet IP
	echoserver.sin_addr.s_addr = INADDR_ANY;	//IP Adress
	echoserver.sin_port = htons(atoi(argv[1]));	//Server Port
//Bind the socket
	serverlen = sizeof(echoserver);
	if (bind(sock, (struct sockaddr *) &echoserver, serverlen) < 0) {
//Error Checking
		perror ("Failed to bind server socket");
		exit(EXIT_FAILURE);}
//Listen
	if (listen(sock, 64) < 0) {
//Error Checking
		perror("listen failed");
		exit(EXIT_FAILURE); }

while(int newSock = accept(sock,(struct sockaddr*)&echoclient, &clientlen)){ 

if (fork()) { //Parent process
//	close(newSock);

	} else {//child process

	std::cerr << "Client connected: " << inet_ntoa(echoclient.sin_addr) << "\n";
	
	while(true){
	//Read a message from the client
	if ((received = read(newSock, buffer, 256)) < 0) {
		perror ("Failed to receive message");
		exit (EXIT_FAILURE);}

	buffer[received] = '\0';
	cout << "RECEIVED: " << received << endl;
	if (!strncmp(buffer,"GET",3)){
	std::cout << "ASKED TO GET" << std::endl;

	if (buffer[4] != '/'){std::cout << "Must start with /"<<std::endl;}
	if (isalpha(buffer[5]))
	{
		strcat(argv[2], "/test.txt");
		cout << argv[2] << endl;
		cout << "ALPHA" << endl;
		if (dup2(newSock,1)<0){perror("socket dup2"); exit(EXIT_FAILURE);}
		execlp("less","less", argv[2],(char*)(NULL));
	}
	else if (buffer[4] == '/')
	{
		if (dup2(newSock,1)<0){perror("socket dup2"); exit(EXIT_FAILURE);}
		execlp("ls","-l",(char*)(NULL));
	}
	else 

	std::cout << "client says: " << buffer << std::endl;	
	//Write the message back to client
	if (write (newSock, buffer, received) != received) {
		perror ("Mismatch in number of bytes");
		exit(EXIT_FAILURE);}
	}
	}
	}
	}	

//close(newSock);
return 0;}
