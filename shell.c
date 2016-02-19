/*
	shell.c

	CS2106 Introduction to Operating Systems
	Assignment 1

	Written by:
	Name: 	Qwek Siew Weng, Melvyn
	Matric:	A0111821X

	Name:	Jay Chua Soon Yao
	Matric:	A0111784H
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 200
#define MAX_PATH_LENGTH 2000

int compareLastChar(char* target, char* c) {

	int lastCharPos = strlen(target) - 1;

	if (target[lastCharPos] == *c) {
		return lastCharPos;
	}

	return -1;
}

// To be polished
void replaceChar(char* toReplace, char oldChar, char newChar) {
	char curr = toReplace[0];
	int i = 0;

	while (curr != '\0') {
		if (curr == oldChar) {
			toReplace[i] = newChar;
		}

		i++;
		curr = toReplace[i];
	}
}

void getInput(char* input) {
	printf("> ");
	fgets(input, MAX_INPUT_LENGTH, stdin);
}

int tokenize(char* output[], char* input, char *delimiter) {
	char *pch = NULL;
	char *rest = input;
	int i = 0;

	//printf ("Input: %s Delimiter %s \n",input, delimiter);
	while ((pch = strtok_r(rest, delimiter, &rest)))
	{
		//printf ("%i %s \n",i,pch);
		output[i] = pch;
		i++;
	}

	return i;
}


int tokenize_old(char* output[], char* input, char delimiter) {
	char *pch = NULL;
	int i = 0;

	pch = strtok(input, &delimiter);
	while (pch != NULL) {
		printf("%i %s \n",i,pch);
		output[i] = pch;
		pch = strtok(NULL, &delimiter);
		i++;
	}

	return i;
}

void runChildProcess(char** paramList) {
	char **pathLocationList;
	pathLocationList = malloc(MAX_PATH_LENGTH);

	char *pathVar = getenv("PATH");
	//printf("%s\n", pathVar);
	int numOfPathLocations = tokenize(pathLocationList, pathVar, ":");

	//printf("numOfPathLocations = %i \n", numOfPathLocations);

	char cmd[MAX_INPUT_LENGTH];
	int lastCharPos = 0;
	for (int i = 0; i < numOfPathLocations; i++) {
		strcpy(cmd, pathLocationList[i]);
		// check if last character is '/'
		lastCharPos = compareLastChar(cmd, "/");

		if (lastCharPos == -1) {
			strcat(cmd, "/");
		}
		
		strcat(cmd, paramList[0]);
		//printf("%i:)-> %s\n",i, cmd);
		execvp(cmd, paramList);
	}
	// Include error message here
	free(pathLocationList);
}

int main(int argc, char *argv[], char *envp[]) {
	pid_t pid;

	while (1) {
		wait(NULL);
		char input[MAX_INPUT_LENGTH];
		getInput(input);
		int temp = compareLastChar(input, "\n");
		if (temp != -1) {
			input[temp] = '\0';
		}

		char **paramList;
		paramList = malloc(MAX_INPUT_LENGTH);

		int numOfParam = tokenize(paramList, input, " ");
		realloc(paramList, numOfParam+1);
		paramList[numOfParam] = NULL;

		if ((pid = fork()) > 0) {
			printf("Loading new process with pID %d\n", pid);
			printf("Parent pID: %d\n", getpid());
		}
		else if (pid == 0) {
			// in child
			runChildProcess(paramList);
			exit(0);
		} else {
			perror("fork error");
			exit(1);
		}
		free(paramList);
	}
	exit(0);
}