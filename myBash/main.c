#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parser.h"

#define MAXN 255



int main(int argc, char *argv[]){
	char line[MAXN];
	/*while (fgets(line, MAXN, stdin)){
		line[strlen(line) - 1] = '\0';
		if (!strcmp(line, "end")){
			break;
		}
		char *argv[] = {"cat", "file1.txt", "file2.txt", 0};
		pid_t i = fork();
		if (i > 0){
			_exit(execvp(argv[0], argv));
		}
	}*/
	fgets(line, MAXN, stdin);
	if (!parser(line)){
		printf("great");
		return 0;
	}
	int fout = open("ans.txt", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	
	dup2(fout, 1);
	close(fout);
	pid_t i = fork();
	char *argvs[] = {"ls", "-l", 0};
	execvp(argvs[0], argv);
	return 0;
}
