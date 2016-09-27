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
const char userInput[] = "3715 199624 21012:10/2016:12.40:Jgn";
char buffer[256];

const char* hostname = "hopper.cs.niu.edu";
int port = 4445;
struct addrinfo hints;
memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype=SOCK_DGRAM;
hints.ai_protocol = 0;
hints.ai_flags=AI_ADDRCONFIG;
struct addrinfo* res = 0;
int err = getaddrinfo(hostname, "4445", &hints, &res);
cout << err << endl;
int received;
int fd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
if (fd==-1){cout << "EE"<<endl;}
cout << fd << endl;

sendto(fd,userInput,sizeof(userInput),0,res->ai_addr,res->ai_addrlen);

//Receive the message back from the server
        unsigned int addrlen = sizeof(res);
        if((received = recvfrom(fd, buffer, 256, 0, (struct sockaddr *) &res, &addrlen))<0){
        perror("Failed to receive"); exit(EXIT_FAILURE);}

return 0;
}

