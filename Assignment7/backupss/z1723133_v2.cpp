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
	int sockfd;
	struct addrinfo hints, *serverinfo, *p;
	int rv;
	char buffer[100];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo("hopper.cs.niu.edu", "4445", &hints, &serverinfo)) != 0){cout << "Err" << endl; exit(1);}

	for (p = serverinfo; p != NULL; p = p->ai_next){cout <<"In l"<<endl;
	if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){cout << "ERR2" << endl; continue;}
}
	cout << p->ai_addr << endl;

return 0;
}
