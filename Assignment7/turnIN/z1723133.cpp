/**********************************************
Amol Shah | CSCI330 | Assignment 7 | 04/20/2016
**********************************************/
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

//*************Format Checking Function prototypes******
//See function definition doc box for more info

//Checks name
bool checkName (string);

//Checks CC#
bool checkCCnum(char []);

//Checks Exp Date
bool checkExpForm(char []);

//Checks Amount
bool checkAmount (char []);

int main(int argc, char ** argv)
{
//UDP variables
	struct sockaddr_in echoserver;	//Structure for server address
	char buffer[256]; 		//Stores response from server
	int 
		echolen, 		//Stores length of transmission to send
		received = 0; 		//Holds returned number of bytes sent
		unsigned int addrlen, 	//Stores length of server address
		sock;			//Socket file descriptor
		
	string name;	//Holds card holder name
	
//Welcome output
        cout << "Welcome to the Credit Card transaction verification utility:" << endl;

//Prompts for user name
        cout << "Enter card holder name (or quit): ";
        std::getline(std::cin, name);

//Continues asking user for trans info until quit for name is entered 
while (name != "quit")
{

//User input variables
        char 
	        CCnum[64] = {'\0'},		//Stores CC num
		CCexpire[64] = {'\0'},		//Stores Expiration Date
		chargeAmount[64] = {'\0'},	//Stores Charge amount
		toSend[256] = {'\0'};	//Cats input using ":" as delim

//Ensure name input is of acceptable length
//Prompts user to re-enter if it is not
	while(!checkName(name))
	{
		cout << "Invalid entry, Enter card holder name: ";
		std::getline(std::cin, name);
	}

//Prompts for CC number
        cout << "Enter CC number: ";
        cin.getline(CCnum, 64);
//Ensures input is digits and of appropriate length
//Prompts user to re-enter if it is not
	while (!checkCCnum(CCnum))
	{
		cout << "Invalid entry, Credit card number should consist of 15 to 16 digits: ";
		cin.getline(CCnum, 64);
	}

//Prompts user for CC expiration date
	cout << "Enter expiration data (MM/YYYY): ";
	cin.getline(CCexpire, 64);
//Ensure input is in format MM/YYYY
//Prompts user to re-enter if it is not
	while (!checkExpForm(CCexpire))
	{
		cout << "Invalid entry, try again (MM/YYYY): ";
		cin.getline(CCexpire, 64);
	}

//Prompts user for charge amount
	cout << "Enter amount: ";
	cin.getline(chargeAmount, 64);
//Ensures amount is in format XX.XX
//Prompts user to re-enter if it is not
	while(!checkAmount(chargeAmount))
	{
		cout << "Invalid entry, try again: ";
		cin.getline(chargeAmount, 64);
	}

	//To create sendable "string"/char array to server
	strcat(toSend, CCnum);
	strcat(toSend, ":");
	strcat(toSend, CCexpire);
	strcat(toSend, ":");
	strcat(toSend, chargeAmount);
	strcat(toSend, ":");
	strcat(toSend, name.c_str());
	
//Create the UDP socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){ 
//Error Checking
		perror("Failed to create socket"); exit(EXIT_FAILURE); }

//Construct the server sockaddr_in structure
	memset(&echoserver, 0, sizeof(echoserver));	//Clear struct
	echoserver.sin_family = AF_INET;		//Internet Address	
	echoserver.sin_addr.s_addr = inet_addr("10.158.56.24");	//Hardcoded IP address
	echoserver.sin_port = htons(4445);		//Server port

//Send the message to the server
	echolen = strlen(toSend);
	if (sendto(sock, toSend, strlen(toSend), 0, (struct sockaddr *) &echoserver, sizeof(echoserver)) != echolen) {	
//Error Checking
		perror("Mismatch in number of sent bytes"); exit(EXIT_FAILURE);}

//Receive the message back from the server
	addrlen = sizeof(echoserver);
	if((received = recvfrom(sock, buffer, 256, 0, (struct sockaddr *) &echoserver, &addrlen))<0){
//Error Checking
	perror("Failed to receive"); exit(EXIT_FAILURE);}

//Null terminate char array
	buffer[received] = '\0';
//Output Response from server
	cout << "Message received: " << buffer << endl;

//Prompts user for card holder name of new transaction
   	cout << "Enter card holder name (or quit): ";
        std::getline(std::cin, name);
        }

     return 0;
}

/*********************************************************
Function: bool checkName(string);
Use: Checks if user input name is of acceptable length
Parameters: String, representing user input of name
Returns: True if format is acceptable(<=64chars), otherwise false
*********************************************************/
bool checkName (string inName)
{
//Checks if name input is of acceptable length
	if (inName.length() > 64)
		return false;
	else 
		return true;
}

/*********************************************************
Function: bool checkCCnum(char []);
Use: Checks if user input of CC num matches acceptable format
Defined by 15 or 16 digits that may be sep with white spaces
Parameters: Char array, representing user input of CC num
Returns: True if format is acceptable, otherwise false
*********************************************************/
bool checkCCnum (char inCCnum[])
{
	int numDigs = 0;	//Keeps track of number if digits

//Counts number of digits in arg
//If any char is not digit returns false
//And ignores white spaces
	for (unsigned int i = 0; i < strlen(inCCnum); i++)
	{
		if ((isdigit(inCCnum[i])))
			numDigs++;

		else if (inCCnum[i] == ' '){}

		else
			return false;
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
	
//Ensures input month is within range
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
	
	return true;
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
		{
			return false;
		}
	}

//Ensures last three chars follow format .XX
	if ((isdigit(inAmount[length-1]) && (isdigit(inAmount[length-2])) && (inAmount[length-3] == '.') && (isdigit(inAmount[length-4]))))
		return true;
	else 
		return false;
}
