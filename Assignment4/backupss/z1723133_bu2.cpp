//Assignment4

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[]){
	cout << "Started in PID: " << getpid()<<endl;

	int status, rs, pid, i = 1;
	char userCommand1[80];
	char userCommand2[80];	
	char * args[5];
	char * args2[5];
	int pipefd[2];
	char ch;
	
	if (pipe(pipefd) == -1){perror("Can't make fork");}
	
	pid = fork();
	
	if (pid == 0)
	{
		cout << "Enter first command: ";
		cin.getline(userCommand1, 80);
			
		for (int g = 0; g < 5; g++){
			args[g] = NULL;}

		args[0] = strtok(userCommand1, " ");
		while (args[i] = strtok(NULL, " "){
			if (args[i] == NULL)
				break;		
		}
	}

/*
	while(strcmp(userCommand1, "quit") != 0) {
	
	           for (int g = 0; g < 5; g++){
                        args[g] = NULL;}

        	args[0] = strtok(userCommand1, " ");
        	while (args[i] = strtok(NULL, " ")) {
                	if (args[i] == NULL)
                        	break;
                	i++;}
		
		i = 1;

		pid = fork();
		if (pid == 0){
			cout << "Child 1" << endl;
			/*close(pipefd[0]);
			close(1);
			dup(pipefd[1]);
			close(pipefd[1]);
        		execvp(args[0], args);*/}
		else{
			wait(0);

				cout << "CHild 2: "<<endl;
				/*close(pipefd[1]);
				close(0);
				dup(pipefd[0]);
				close(pipefd[0]); 
			
				while(read(0, &ch, 1) == 1){
					write(1, &ch, 1);
				}*/		
		    	}

	cout << "Enter Command 1: ";
	cin.getline(userCommand1, 80);
	}
*/
	return 0;}
