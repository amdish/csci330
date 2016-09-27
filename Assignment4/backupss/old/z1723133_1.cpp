//Assignment 4


#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
	int rs, pid, count = 1;
	char userCommand1[80]; 
	char userCommand2[80];
	char * args[5];

	cout << "Started main prog in " << getpid() << endl;

	while(cin.getline(userCommand1, 80) && (strcmp(userCommand1, "quit") != 0))
	{
		cout << "Working" << endl;
		args[0] = strtok(userCommand1, " ");
		
		while((args[count] = strtok(NULL, " ")) && args[count] != NULL)
		{
			count++;
		}
		
		for (int i = 0; i < count; i++)
		{
			cout << "Arg: " << i << " " << args[i] << endl;
		}
		count = 1;
	}

	return 0;
}
