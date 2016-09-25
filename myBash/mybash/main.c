#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parser.h"

#define MAXN 255

int main(){
	char line[MAXN];
	
	while (1){
		fgets(line, MAXN, stdin);
		if (!strcmp(line, "exit\n")){
			break;
		}
		
		char listOfWords[MAXN][MAXN];
		
		int numOfWords = parser(line, listOfWords);
		
		comd listOfComds[MAXN];
		
		int numOfComds = getCommands(listOfWords, numOfWords, listOfComds);
		int i = 0;
		int isUsePipe = 0;
		int pipefd[2];
		for (i; i < numOfComds; ++i){
			if (isUsePipe == 1){
				isUsePipe = 0;
			}
			if (isUsePipe == 2){
				isUsePipe = 1;
			}
			
			if (listOfComds[i].isPipe){
				int corPipe = pipe(pipefd);
				isUsePipe = 2;
			}
			pid_t pid = fork();
			
			int status = -1;
			
			if (pid == 0){
				if (isUsePipe == 1){
					dup2(pipefd[0], 0);
					close(pipefd[0]);
					isUsePipe = 0;
				}
				if (listOfComds[i].redirin){
					int  in = open(listOfComds[i].strin, O_RDONLY);
					dup2(in, 0);
					close(in);
				}
				
				if (listOfComds[i].redirout){
					int  out = open(listOfComds[i].strout, O_RDWR| O_TRUNC | O_CREAT);
					dup2(out, 1);
					close(out);
				}
				if (isUsePipe == 2){
					dup2(pipefd[1], 1);
					close(pipefd[1]);
					isUsePipe = 1;
				}
				
				execvp(listOfComds[i].argv[0], listOfComds[i].argv);
				_exit(&status);
			}
		}
	}
	
	return 0;
}



