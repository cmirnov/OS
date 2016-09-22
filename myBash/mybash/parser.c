//#include <stdio.h>
//#include <string.h>
#include "parser.h"

//#define MAXN 255

void getWord (char* str, int* i, char word[]){
	for(; str[*i] && str[*i] == ' '; (*i)++){}
	int j = 0;
	for(; str[*i] && str[*i] != ' ' && str[*i] != '\n'; (*i)++, ++j){
		word[j] = str[*i];
	}
	word[j] = '\0';
	return;
}

int parser(char* str, char listOfWords[255][255]){
	int i = 0, j = 0;
	for(;str[i] && str[i] != '\n'; ++j, ++i){
		getWord(str, &i, listOfWords[j]);
	}
	return j;
}


