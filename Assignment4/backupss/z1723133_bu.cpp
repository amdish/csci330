//Assignment4

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Started in PID: " << getpid()<<endl;

	char buffer[30];	
	int status, rs, pid, i = 1;
	char userCommand1[80];
	char userCommand2[80];	
	char * args[5];
	char * args2[5];
	int pipefd[2];
	
	pipe(pipefd);
	pid = fork();
	
	if (pid == 0) { //Child process 1
/*		close(pipefd[0]);
		close(1);
		dup(pipefd[1]);
		close(pipefd[1]);
*/
        while(cin.getline(userCommand1, 80) && strcmp(userCommand1, "quit") != 0){

                for (int g = 0; g < 5; g++)
                {
                        args[g] = NULL;
                }

        args[0] = strtok(userCommand1, " ");
        while (args[i] = strtok(NULL, " ")) {
                if (args[i] == NULL)
                        break;

                i++;
        }

        execvp(args[0], args);

	}

	else { // Paraent process
		wait(0);
		pid = fork();
		if (pid == 0) { // Child process 2
			close(pipefd[1]);
			close(0);
			dup(pipefd[0]);
			close(pipefd[0]);
		
			execvp(args[0], args);
		}
		else { wait(0);}
	}

	}

/*	cout << "Enter first command: ";

	while (cin.getline(userCommand1,80) && strcmp(userCommand1,"quit")!=0)
	{
		cout << "Enter second command: ";
		cin.getline(userCommand2,80);	

		args[0] = strtok(userCommand1, " ");
		while((args[i] = strtok(NULL, " ")) != NULL && i <=5)
		{
			i++;
		}

		i = 1;

		args2[0] = strtok(userCommand2, " ");
		while((args[i] = strtok(NULL, " ")) != NULL && i <=5)
		{
			i++;
		}
	
		i = 1;
		
		pid = fork();
		if (pid == 0)
		{
			close(1);
			dup (pipefd[1]);
			close(pipefd[1]);
			
			rs = execvp(args[0], args);	
			
			pid = fork();
			if (pid == 0);
			{
				close(0);
				dup (pipefd[0]);
				close(pipefd[0]);
	
				rs = execvp(args2[0], args2);
			}	
		}
		
		wait(0);
	
		cout <<"Enter first command: ";

	} 
*/
	return 0;
}

/*
                while (argument[count] != NULL) {
                        cout << argument << endl;
                        argument[count] = strtok (NULL, " ");
                        count++;}
*/
