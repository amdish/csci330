#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

int main(int argc, char * argv[])
{	
	int pid, rs, status;		//Variables to check return value of system calls
	int count = 1;		//Keeps count of number of options
	int pipefd[2];		//Pipe file descriptors 
	char userCommand1[80];	//Stores user input
	char userCommand2[80];	
	char * cmd1Args[5];	//Stores command and options
	char * cmd2Args[5];	
	int stdINfd = dup(0);	//Stores original stdin file descriptor

	cout <<"MAIN: " << getpid();

	//Loop to control main parent process. Gather user input.	
	cout << "Enter Command One: ";	
	while((cin.getline(userCommand1,80)) && (strcmp(userCommand1,"quit")!=0)) {
	
		cout << "Enter Command Two: ";
		cin.getline(userCommand2, 80);
		cout << "(1) You entered:  " << userCommand1 << endl;
		cout << "(2) You entered:  " << userCommand2 << endl;

		//Separates user input into command and options
		cmd1Args[0] = strtok(userCommand1, " ");
		while((cmd1Args[count] = strtok(NULL, " ")) !=0 ){count++;}
		count = 1;

		//Separates user input into command and options
		cmd2Args[0] = strtok(userCommand2, " ");
		while((cmd2Args[count] = strtok(NULL, " ")) !=0 ){count++;}
		count = 1;	

		//Creates pipe
		rs = pipe(pipefd);
		if (rs != 0)
		{ 	
			perror("Error creating pipe");
			exit(-259);
		}
		
		pid = fork();
		if (pid == -1)
		{
			perror("Error creating fork");
			exit(-1);	
		}	

		if (pid == 0) { //Child process
			cout << "CHILD 1: " << getpid() << endl;
			close(pipefd[0]);
		//	close(1);
		//	dup(pipefd[1]);
			dup2(pipefd[1], 1);
			close(pipefd[1]);
			
			rs = execvp(cmd1Args[0], cmd1Args);
			if (rs == -1)
			{
				perror("Unable to run command 1");
				exit(-259);
			}
		}
		else { //Parent process
			
			close(pipefd[1]);
		//	close(0);
		//	dup(pipefd[0]);
			dup2(pipefd[0], 0);
			close(pipefd[0]);
			
			waitpid(-1, &status, 0);	//Wait for child 1
	//		cout << "STAT:::::::::: " << WEXITSTATUS(status) << endl;
			pid = fork();
			if (pid == -1)
			{
				perror("Error creating fork");
				exit(-1);
			}		
	
			if(pid == 0)
			{
				rs = execvp(cmd2Args[0], cmd2Args);	
				if (rs == -1)
				{
					perror("Unable to run command 2");
					exit(-1);
				}
			}
			else
			{
				wait(NULL);
			}
		}

	//Change standard input back to stdin(keyboard)
	dup2(stdINfd,0);
	
	cout <<"THIS: " << getpid() << endl;
	cout << "Enter Command One: ";
rs = 0;
	}

	return 0;
}
