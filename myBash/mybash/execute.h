#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#ifndef EXECUTE_H
#define EXECUTE_H

#define MAXN 255


typedef struct {
	char *strin;
	char *strout;
	int redirout;
	int redirin;
	int isPipe; // it is true when "|" follows after this comd
	char *argv[MAXN];
}comd;

void initComd(comd *t);

#endif