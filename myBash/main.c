#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MAXN 255

int main(int argc, char *argv[]){
	char line[MAXN];
	while (fgets(line, MAXN, stdin)){ // && strcmp(line, "end")) {
		line[strlen(line) - 1] = '\0';
		if (!strcmp(line, "end")){
			break;
		}
		pid_t i = fork();
		if (i > 0){
			int status = -1;
			printf("safds");
			execv(line, (char *[]){line, NULL});
			if (wait(&status) >= 0){
				printf("strange");
			}
			_exit(0);
		}
	}
	
	return 0;
}
