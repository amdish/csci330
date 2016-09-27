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
/*
using std::cout;
using std::endl;
using std::*/

int main (int argc, char ** argv)
{
//Check for correct arguments and display usage instruction
	if (argc < 2) {
		cout << "Incorrect Arguments\n"
			 << "Correct usage is: 'port number' 'root directory'" << endl;
	}

	char buffer[256]; 	//Holds client response
	
	int 	
		sock,			//Socket file descriptor 
		received;

	unsigned int	
			serverlen,
			clientlen;

	struct sockaddr_in 	echoserver, 	//Server address
						echoclient;		//client address

	DIR *dirp;					//Pointer to directory 
	struct dirent *dirEntry;	//Pointer to directory entry

//Create the TCP socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//Error Checking
		perror("Failed to create socket");
		exit (EXIT_FAILURE);
	}

//Construct the server sockaddr_in structure
	memset(&echoserver, 0, sizeof(echoserver));	//Clear struct
	echoserver.sin_family = AF_INET;			//Internet IP
	echoserver.sin_addr.s_addr = INADDR_ANY;	//IP Adress
	echoserver.sin_port = htons(atoi(argv[1]));	//Server Port

//Bind the socket
	serverlen = sizeof(echoserver);
	if (bind(sock, (struct sockaddr *) &echoserver, serverlen) < 0) {
//Error Checking
		perror ("Failed to bind server socket");
		exit(EXIT_FAILURE);
	}

//Listen for incoming connection request
	if (listen(sock, 64) < 0) {
//Error Checking
		perror("listen failed");
		exit(EXIT_FAILURE); 
	}
	while(int newSock = accept(sock,(struct sockaddr*)&echoclient, &clientlen)) 
	{ 
		if (fork()) { //Parent process
			close(newSock);	//Closes connection with client to keep listening
		}
		else 
		{ //child process / comms with connected client
//Output on server side with client information
			cout << "Client connected: " << inet_ntoa(echoclient.sin_addr) << endl;
//Keeps connection open
			while(true)
			{
//Read a message from the client
				if ((received = read(newSock, buffer, 256)) < 0) {
//Error checking for received sys call
					perror ("Failed to receive message");
					exit (EXIT_FAILURE);
				}
				buffer[received] = '\0';	//Null terminate client input
//Checks for correct "trigger" input command
				if (!strncmp(buffer,"GET",3)) 
				{ 
					cout << "ASKED TO GET" << endl;
//Error if client input is incorrect
					if (buffer[4] != '/') 
					{ 
						cout << "Input must follow format GET path, please try again" << endl; 
						//exit(EXIT_FAILURE);
					}	 
					char path[200];
					int count = 0;
//Continues only if valid directory or filename charecter
					if (isalpha(buffer[5]) || isdigit(buffer[5])) {
//Separates path from client input
						while(buffer[count] != '\0')
						{
							path[count] = buffer[count+4];
							count++;
						}
						path[count] = '\0';
						cout << "THE PATH: "<<path<<endl;
						strcat(argv[2], path);
						cout << argv[2] << endl;
						cout << "ALPHA" << endl;
						//if (dup2(newSock,1)<0){perror("socket dup2"); exit(EXIT_FAILURE);}
						//execlp("less","less", argv[2],(char*)(NULL)); 
					}
//Shows files in webserver root
					else if (buffer[4] == '/')
					{
//Checks for substring..
						int count2 = 4;
						while((buffer[count2] != '\0') && (buffer[count2+1] != '\0'))
						{
							cout << buffer[count2] << endl;
							if ((buffer[count2] == '.') && (buffer[count2+1] == '.'))
							cout << buffer[count2] << " No SUBSTRINGS"<<endl;
							count2++;
						}							
//Duplicate socket descriptor into standard output
						if (dup2(newSock,1) < 0) { 
							perror("socket dup2"); 
							exit(EXIT_FAILURE);
						}
//Opens directory specified in arg 2 of server launch command
						if ((dirp = opendir(argv[2])) == 0) { 
//Error Checking
							perror(argv[2]); 
							exit(EXIT_FAILURE);
						}
//Continues reading entries until no more
						while((dirEntry = readdir(dirp)) != NULL) 
						{
							if (dirEntry->d_name[0] != '.') {
//Transmits/Writes each entry to the client
								if (write(newSock,dirEntry->d_name,strlen(dirEntry->d_name)) != strlen(dirEntry->d_name))
									{perror("Unable to transmit, please try again");exit(EXIT_FAILURE);}
								cout << endl;
							}						
						}//End of print directory contents
					}//End of show contents of director
				}//End of GET dec tree
				else 
					cout << "Input must follow format GET path, please try again" << endl; 
			}//End of keep connection open loop
		}//End of child process
	}//End of accept connection loop	
//close(newSock);
return 0;
}

/*	if (write (newSock, buffer, received) != received) {
		perror ("Mismatch in number of bytes");
		exit(EXIT_FAILURE);}*/
