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
	cout << "Started main prog in " << getpid() << endl;

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
		pid = fork();
		rs = pipe(pipefd);
		if(rs<0){perror("Can't create pipe");}

		if (pid == 0){
			cout << "In Child"<<endl;
			for (int i = 0; i < args1Count; i++)
			{
                        	cout << "Arg: " << i << " " << cmd1Args[i] << endl;
                	}
			
			close(pipefd[0]);
			close(1);
			dup(pipefd[1]);
			close(pipefd[1]);
			execlp("ls","-l",(char*)NULL);

		}//End of Child 1
	
		else {wait(0); cout<<"In parent"<<endl;}
		
		args1Count = 1;
		cout << "CCC"<<endl;	

	}//End of while loop

	return 0;
}
