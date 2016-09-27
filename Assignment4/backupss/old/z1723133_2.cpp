#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
	int rs, pid, count = 1;
	char inCmd1[80]; 
	char inCmd2[80];
	char * cmd1Args[5];
	char * cmd2Args[5];

	cout << "Started main prog in " << getpid() << endl;

	while(cin.getline(inCmd1, 80) && (strcmp(inCmd1, "quit") != 0))
	{
	//	cout << "Enter Command 2: ";
	//	cin.getline(inCmd2, 80);		

		cout << "Working" << endl;
		cmd1Args[0] = strtok(inCmd1, " ");
		
		while((cmd1Args[count] = strtok(NULL, " ")) && cmd1Args[count] != NULL)
		{
			count++;
		}
		
		for (int i = 0; i < count; i++)
		{
			cout << "Arg: " << i << " " << cmd1Args[i] << endl;
		}
		count = 1;

		pid = fork();
		
			

	}//End of while loop

	return 0;
}
