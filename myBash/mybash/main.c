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
		//line[strlen(line) - 1] = '\0';
	//	printf("%s", line);
		if (!strcmp(line, "end\n")){
			//printf("sda");
			break;
		}

		char listOfWords[MAXN][MAXN];
		
		int numOfWords = parser(line, listOfWords);
		
		int redirin = 0, redirout = 0;
		
		char *argv[numOfWords];
		
		int i, j = 0;
		
		char *strin, *strout;
		
		for (i = 0; i < numOfWords; ++i){
			if (!strcmp(listOfWords[i], ">")){
				i++;
				strout = listOfWords[i];
				//printf("%s", strout);
				redirout = 1;
				continue;
			}	
			if(!strcmp(listOfWords[i], "<")){
				i++;
				strin = listOfWords[i];
				redirin = 1;
				continue;
			}
			argv[j] = listOfWords[i];
			j++;
		}
		
		pid_t pid = fork();
		int status = -1;
		
		if (pid == 0){
			argv[j] = NULL;
			if (redirin){
				int  in = open(strin, O_RDONLY);
				dup2(in, 0);
				close(in);
			}
			
			if (redirout){
				int  out = open(strout, O_RDWR| O_TRUNC | O_CREAT); // S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				//printf("%d", out);
				dup2(out, 1);
				close(out);
			}
			execvp(argv[0], argv);
		}
		else{
			wait(&status);
		}
		
	}
	return 0;
}



