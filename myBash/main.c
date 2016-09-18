#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXN 255

int main(int argc, char *argv[]){
	//char line[MAXN];
	/*while (fgets(line, MAXN, stdin)){ // && strcmp(line, "end")) {
		//fputs(line, stdin);
		printf("%s", line);
	}*/
	pid_t i = fork();
	if (i > 0){
		execv("pic.png", argv[1]);
	}
	return 0;
}
