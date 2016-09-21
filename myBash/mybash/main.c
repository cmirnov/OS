//#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>	
#include "parser.h"

#define MAXN 255



int main(){
	char line[MAXN];
	while (fgets(line, MAXN, stdin)){

		line[strlen(line) - 1] = '\0';
		
		if (!strcmp(line, "end")){
			break;
		}

		char listOfWords[MAXN][MAXN];
		
		int numOfWords = parser(line, listOfWords);
		
		int redirin = 0, redirout = 0;
		
		char *argv[numOfWords];
		
		int i;
		
		char *strin, *strout;
		
		for (i = 0; i < numOfWords; ++i){
			if (!strcmp(listOfWords[i], ">")){
				i++;
				strout = listOfWords[i];
				redirout = 1;
			}	
			if(!strcmp(listOfWords[i], "<")){
				i++;
				strin = listOfWords[i];
				redirin = 1;
			}
			argv[i] = listOfWords[i];
		}
		
		pid_t j = fork();
		
		argv[i] = NULL;
		
		
		/*if (redirin){
			int  in = open(strin, O_RDONLY);
			dup2(in, 0);
			close(in);
		}*/
		
		if (redirout){
			 int  out = open(strout, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			dup2(out, 1);
			close(out);
		}
		execvp(argv[0], argv);
		
			
		/*else{
			fgets(line, MAXN, stdin);
				
			
			pid_t i = fork();
			char *argvs[] = {"ls", "-l", 0};
			execvp(argvs[0], argv);
		}*/
	}
	return 0;
}



