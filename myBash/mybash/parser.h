#include <stdio.h>
#include <stdlib.h>
#include "execute.h"

#ifndef PARSER_H
#define PARSER_H

void getWord (char* str, int* i, char word[]);

int getCommands(char listOfWords[255][255], int n, comd listOfComd[255]);

int parser(char* str, char listOfWords[255][255]);


#endif
