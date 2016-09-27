#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]) {
	int rs, pid;
	int args1Count = 1;
	int args2Count = 1;
	char inCmd1[80]; 
	char inCmd2[80];
	char * cmd1Args[5];
	char * cmd2Args[5];
	int pipefd[2];
	cout << "tarted main prog in " << getpid() << endl;

	while(cin.getline(inCmd1, 80) && (strcmp(inCmd1, "quit") != 0))
	{
	//	cout << "Enter Command 2: ";
	//	cin.getline(inCmd2, 80);		

		cout << "Working" << endl;
		cmd1Args[0] = strtok(inCmd1, " ");
		
		while((cmd1Args[args1Count] = strtok(NULL, " ")) && cmd1Args[args1Count] != NULL)
		{
			args1Count++;
		}

		rs = pipe(pipefd);
		if(rs<0){perror("NO PIPE");}

		pid = fork();
		if(rs<0){perror("Can't create FORK");}

		if (pid == 0){
			cout << "In Child"<<endl;i/*
			for (int i = 0; i < args1Count; i++)
			{
                        	cout << "Arg: " << i << " " << cmd1Args[i] << endl;
                	}*/
			
			close(pipefd[1]);
			close(0);
			dup(pipefd[0]);
			close(pipefd[1]);
		}//End of Child 1
	
		else {
			cout<<"In parent"<<endl;
			close(pipefd[1]);
			close(0);
			dup(pipefd[0]);
			close(pipefd[0]);			
			cout <<"From Parent"<<endl;
			wait(0); 
			}
		
		args1Count = 1;
		cout << "CCC"<<endl;	

	}//End of while loop

	return 0;
}
