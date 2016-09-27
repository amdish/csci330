#include <iostream>


int main(){

	int pipefd[2], rs;	

	if (rs == 0)
	{//Child process
	
	/*	close(1);
		dup(pipefd[1]);
		close(pipefd[0]);
*/
	//	rs = execl("usr/bin/wc", "wc", (char *) NULL);
	}
	else 
	{//Parent process
		
/*		close(0);
		dup(pipefd[0]);
		close(pipefd[1]);
*/
		wait(0);
		
		rs = execl("/bin/ls","ls",(char *) NULL);
	}

	return 0;
}
