#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 80

// To be polished
void replaceChar(char* toReplace, char oldChar, char newChar) {
	char cur=toReplace[0];
	int i=0;

	while(cur!='\0'){
		//printf("%i %c\n",i, cur);
		if(cur==oldChar)
			toReplace[i]=newChar;
		i++;
		cur=toReplace[i];
	}
}

void getInput(char* input) {
	printf("> ");
	fgets(input, MAX_INPUT_LENGTH, stdin);
}

int tokenize(char* output[], char* input, char delimiter) {
	char *pch;
	int i = 0;

	pch = strtok (input, &delimiter);
	while (pch != NULL)
	{
		output[i] = pch;
		//printf ("%i %s\n",i,pch);
		pch = strtok (NULL, &delimiter);
		i++;
	}

	return i;
}

int main(int argc, char *argv[], char *envp[]) {
	pid_t pid;

	while (1) {
		wait(NULL);
		char input[MAX_INPUT_LENGTH];
		printf("my pr %d", getpid());
		getInput(input);
		replaceChar(input, '\n', '\0');

		char **paramList;
		paramList = malloc(MAX_INPUT_LENGTH);

		int numOfParam = tokenize(paramList, input, ' ');
		realloc(paramList, numOfParam+1);
		paramList[numOfParam] = NULL;

		if ((pid = fork()) > 0) {
			printf("Loading new process with pID %d\n", pid);
			printf("Parent pID: %d\n", getpid());
		}
		else if (pid == 0) {
			// in child
			char cmd[MAX_INPUT_LENGTH];
			strcpy(cmd, "/bin/");
			strcat(cmd, paramList[0]);
			//printf("cmd = %s", paramList[1]);

			//execvp(cmd, paramList);
			execvp(cmd, paramList);

			exit(0);
		} else {
			perror("fork error");
			exit(1);
		}
		free(paramList);
	}
	
	exit(0);
}