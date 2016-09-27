#include <iostream>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <cstring>
#include <string>

using namespace std;

int main(){

	int pid;
	int pipefd[2];
	char buffer[100];
	cout << "MAIN: " << getpid() << endl;
	pipe(pipefd);
	pid = fork();
	char ch;
	char * args[5];

	if (pid == 0){
		cout <<"CHILD: " <<getpid()<<endl;
		close(pipefd[0]);
		close(1);	
		dup(pipefd[1]);		
		close(pipefd[0]);	
//		cout <<"PIPING THIS";	
		execlp("ls","ls", "-i", (char*)NULL);
		}

	else {
		close(pipefd[1]);
		close(0);
		dup(pipefd[0]);
		close(pipefd[0]);
		wait(NULL);
		
//		while(read(0,&ch,1)){cout << ch;}		
		
	
		execlp("wc", "wc", "-c", (char *)NULL); 
		
	
	}

	return 0;
}
