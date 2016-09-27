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

//Function prototypes**********************
//Check name
bool checkName (string);
//Check CC#
bool checkCCnum(char []);
//Check Exp Date
bool checkExpForm(char []);
//Check Amount fx
bool checkAmount (char []);

int main(int argc, char ** argv)
{
//UDP variables
	struct sockaddr_in echoserver;	//Structure for server address
	char buffer[256]; 		//Stores response from server
	int 
		echolen, 		//Stores length sent transmission
		received = 0; 		//Number bytes sent
		unsigned int addrlen, 	//Stores length of server address
//		serverlen,	
		sock;			//Socket file descriptor

	//********TO REMOVE
		const char userInput[] = "3715 199624 21012:10/2016:12.40:Jgn";

//User input variables
	string name;
        char 
	        CCnum[64],		//Stores CC num
		CCexpire[64],		//Stores Expiration Date
		chargeAmount[64],	//Stores Charge amount
		toSend[256] {'\0'};	//Cats input using ":" as delim
		
//Welecome output
        cout << "Welcome to the Credit Card transaction verification utility:" << endl;

//Prompts for user name
        cout << "Enter card holder name: ";
        std::getline(std::cin, name);
//Ensure name input is of acceptable length
//Prompts user to re-enter if it is not
	while(!checkName(name))
	{
		cout << "Invalid entry, Enter card holder name: ";
		std::getline(std::cin, name);
	}

//Prompts for CC number
//Ensures input is digits and of appropriate length
        cout << "Enter CC number: ";
        cin.getline(CCnum, 64);
	while (!checkCCnum(CCnum))
	{
		cout << "Invalid entry, Credit card number should consist of 15 to 16 digits" << endl;
		cin.getline(CCnum, 64);
	}

//Prompts user for CC expiration date
//Ensure input is in format MM/YYYY
	cout << "Enter expiration data (MM/YYYY): ";
	cin.getline(CCexpire, 63);
	while (!checkExpForm(CCexpire))
	{
		cout << "Invalid entry, try again (MM/YYYY): ";
		cin.getline(CCexpire, 63);
	}


//Prompts user for charge amount
//Ensures amount is in format XX.XX
	cout << "Enter amount: ";
	cin.getline(chargeAmount, 63);

	while(!checkAmount(chargeAmount))
	{
		cout << "Invalid entry, try again: ";
		cin.getline(chargeAmount, 63);
	}

	//To create sendable "string"/char array to server
	strcat(toSend, CCnum);
	strcat(toSend, ":");
	strcat(toSend, CCexpire);
	strcat(toSend, ":");
	strcat(toSend, chargeAmount);
	strcat(toSend, ":");
	strcat(toSend, name.c_str());
	cout << toSend << endl;	
	

//Create the UDP socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){//Error Checking
		perror("Failed to create socket"); exit(EXIT_FAILURE);}

//Construct the server sockaddr_in structure
	memset(&echoserver, 0, sizeof(echoserver));	//Clear struct
	echoserver.sin_family = AF_INET;		//Internet IP	
	echoserver.sin_addr.s_addr = inet_addr("10.158.56.24");
	echoserver.sin_port = htons(4445);		//Server port

//Send the message to the server
	echolen = strlen(toSend);
	if (sendto(sock, toSend, strlen(toSend), 0, (struct sockaddr *) &echoserver, sizeof(echoserver)) != echolen){perror("Mismatch in number of sent bytes"); exit(EXIT_FAILURE);}

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

/*********************************************************
Function: bool checkName(string);
Use: Checks if user input name  matches acceptable format
Parameters: String, representing user input of name
Returns: True if format is acceptable, otherwise false
*********************************************************/
bool checkName (string inName)
{
//Ensure name input is of acceptable length
//Prompts user to re-enter if it is not
	if (inName.length() > 64)
		return false;
	else 
		return true;
}

/*********************************************************
Function: bool checkCCnum(char []);
Use: Checks if user input of CC num matches acceptable format
Parameters: Char array, representing user input of CC num
Returns: True if format is acceptable, otherwise false
*********************************************************/
bool checkCCnum (char inCCnum[])
{
	int numDigs = 0;	//Keeps track of number if digits

	//Counts number of digits in arg
	//If any char is not digit returns false
	for (int i = 0; i < strlen(inCCnum); i++)
	{
		if (isdigit(inCCnum[i]))
		{
			numDigs++;
		}
		else if (!isdigit(inCCnum[i]))
		{
			return false;
		}
	}

	//Ensures number of digits are between 15 and 16
	if (numDigs >= 15 && numDigs <= 16)
		return true;
	else
		return false; 
}

/*********************************************************
Function: bool checkExpForm(char []);
Use: Checks if user input of exp date matches MM/YYYY
Parameters: Char array, representing user input of exp date
Returns: True if format is acceptable, otherwise false
*********************************************************/
bool checkExpForm(char inExpire[])
{
	//Stores length of arguemnt char array
	int length = strlen(inExpire);

	//Checks for correct number of chars
	if (length != 7)
		return false;
	
	//Checks that each char is digit or '/'
        for (int i = 0; i < length-1; i++)
        {
                if (!((isdigit(inExpire[i])) || (inExpire[i] == '/')))
		{
			return false;
		}
        }
	
	//Ensures month is correct and within range
	if (inExpire[0] == '0')
	{
		if (inExpire[1] == '0')
			return false;
	}
	else if (inExpire[0] == '1')
	{	
		if (((inExpire[1] == '0') || (inExpire[1] == '1') || (inExpire[1] == '2')))
			return true;
		else
			return false;
	}
	else 
		return false;
	
	return true;	//Returns true if passes all checks	
}

/*********************************************************
Function: bool checkAmount(char []);
Use: Checks if input amount format is XX.XX
Parameters: Char array, representing user input of amount
Returns: True if format is accetable, otherwise false
*********************************************************/
bool checkAmount (char inAmount[])
{
	//Stores length of arguemnt char array
	int length = strlen(inAmount);

	//Checks if all charecters in arg are digits or periods
	for (int i = 0; i < length-1; i++)
	{
		if (!((isdigit(inAmount[i])) || (inAmount[i] == '.')))
			{return false;}
	}

	//Ensures last three chars follow format .XX
	if ((isdigit(inAmount[length-1]) && (isdigit(inAmount[length-2])) && (inAmount[length-3] == '.') && (isdigit(inAmount[length-4]))))
		return true;
	else 
		return false;
}
