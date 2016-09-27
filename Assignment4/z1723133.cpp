/********************************************************
Amol Shah | CSCI 330 | Assignment 4 | 03.21.16
Input: Two commands with/without options.
Output: The result of using command 1s output as input for command 2. 
Purpose: This program prompts the user for two commands, utilizing forks, pipe, dup, and exec. The program runs command 1 and pipes output to child 2, which runs the second command. The output from child 2 is displayed on screen. 
**********************************************************************/

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

int main(int argc, char *argv[])
{	
	int
		pid, 				//Variables to store return/exit value of system calls
		rs,
		status,
		eStat, 
		count = 1,			//Keeps count of number of options
		pipefd[2],			//Pipe file descriptors 
		stdINfd = dup(0);	//Stores original stdin file descriptor
	char 
		userCommand1[80],	//Stores user input
		userCommand2[80],	
		*cmd1Args[5],		//Stores separated user input as command and options
		*cmd2Args[5];	

	//Asks user for first command
	cout << "Enter command one (include args) or quit: ";	
	
	//Loop to control main parent process. 
	//Gathers user input. 
	//Exits if user enters quit for com 1	
	while((cin.getline(userCommand1,80)) && (strcmp(userCommand1,"quit")!=0)) 
	{
		//Prompts user for second command
		cout << "Enter command two (include args): ";
		cin.getline(userCommand2, 80);

		//Separates user input 1 into command and options
		cmd1Args[0] = strtok(userCommand1, " ");
		while((cmd1Args[count] = strtok(NULL, " ")) !=0)
		{
			count++;	//Running total of number of options
		}
		count = 1;		//Reset count

		//Separates user input 2 into command and options
		cmd2Args[0] = strtok(userCommand2, " ");
		while((cmd2Args[count] = strtok(NULL, " ")) !=0)
		{
			count++;	//Running total of number of options
		}
		count = 1;		//Reset count	

		//Creates pipe
		rs = pipe(pipefd);

		//Pipe error checking
		if (rs != 0)
		{		 	
			perror("Error creating pipe");
			exit(-1);
		}
		
		//Creates fork
		pid = fork();
		
		//Fork error checking
		if (pid == -1)
		{		
			perror("Error creating fork");
			exit(-1);	
		}	
		
		//Child process 1
		if (pid == 0) 
		{ 	
			close(pipefd[0]);		//Closes read end of pipe
			dup2(pipefd[1], 1);		//Replaces stdout with write end of pipe
			close(pipefd[1]);		//Closes write end of pipe
			
			rs = execvp(cmd1Args[0], cmd1Args);		//Calls execv for user input
			
			//Exec error checking
			if (rs == -1)
			{	
				perror(cmd1Args[0]);
				exit(-1);
			}
		}
		
		//Parent Process
		else
		{		
			close(pipefd[1]);		//Closes write end of pipe
			dup2(pipefd[0], 0);		//Replaces stdin with read end of pipe
			close(pipefd[0]);		//Closes read end of pipe
			
			waitpid(-1, &status, 0);	//Waits for child 1
			eStat = WEXITSTATUS(status);
	
			//Forks again if child 1 was able to sucessfully complete exec	
			if (eStat == 0)
			{
				//Second fork 
				pid = fork();
				
				//Fork error checking
				if (pid == -1)
				{	
					perror("Error creating fork");
					exit(-1);
				}		
	
				//Child process 2
				if(pid == 0)
				{	
					rs = execvp(cmd2Args[0], cmd2Args);	
					
					//Exec error checking
					if (rs == -1)
					{
						perror(cmd2Args[0]);
						exit(-1);
					}
				}

				//Parent process
				else	
				{
					wait(NULL);		//Waiting for second child
				}
			}
		}

	dup2(stdINfd, 0);		//Changes standard input back to stdin(keyboard)	

	//Prompts user for first command
	cout << "Enter command one (include args) or quit: ";	

	}

	return 0;
}
