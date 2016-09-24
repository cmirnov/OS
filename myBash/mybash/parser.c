//#include <stdio.h>
//#include <string.h>
#include "parser.h"
#include "execute.h"


//#ifndef PARSER_C
//#define PARSER_C
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

int getCommands(char listOfWords[255][255], int n, comd listOfComds[255]){
	int i = 0, j = 0, k = 0;
	comd *t = (comd*)malloc(sizeof(comd));
	initComd(t);
	for (i; i < n; ++i){
		//printf("%s\n", listOfWords[i]);
		if (!strcmp(listOfWords[i], ">")){
			i++;
			t->strout = listOfWords[i];
			t->redirout = 1;
			continue;
		}	
		if (!strcmp(listOfWords[i], "<")){
			i++;
			t->strin = listOfWords[i];
			t->redirin = 1;
			continue;
		}
		if (!strcmp(listOfWords[i], "|")){
			//printf("work");
			t->isPipe = 1;
			t->argv[k] = NULL;
			listOfComds[j] = (*t);
			free(t);
			t = (comd*)malloc(sizeof(comd));
			initComd(t);
			j++;
			k = 0;
			continue;
		}
		if (!strcmp(listOfWords[i], "&&")){
			t->argv[k] = NULL;
			listOfComds[j] = (*t);
			free(t);
			t = (comd*)malloc(sizeof(comd));
			initComd(t);
			j++;
			k = 0;
			continue;
		}
		t->argv[k] = listOfWords[i];
		k++;
	}
	t->argv[k] = NULL;
	listOfComds[j] = (*t);
	free(t);
	j++;
	return j;
}


//#endif