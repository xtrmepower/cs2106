/*
	shell2.c

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
#define MAX_ERROR_MSG_LENGTH 200
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

	while ((pch = strtok_r(rest, delimiter, &rest)))
	{
		output[i] = pch;
		i++;
	}

	return i;
}

void runChildProcess(char** paramList) {
	char **pathLocationList;
	pathLocationList = malloc(MAX_PATH_LENGTH);

	char *pathVar = getenv("PATH");
	int numOfPathLocations = tokenize(pathLocationList, pathVar, ":");

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
	char errorMsg[MAX_ERROR_MSG_LENGTH];
	perror(errorMsg);
	printf("Shell error: %s", errorMsg);
	
	free(pathLocationList);
}

int main(int argc, char *argv[], char *envp[]) {
	pid_t pid;

	while (1) {
		wait(NULL);

		char input[MAX_INPUT_LENGTH];
		getInput(input);

		// See if the last character is a newline character
		int result = compareLastChar(input, "\n");
		if (result != -1) {
			// If it is, replace it with a null terminator
			input[result] = '\0';
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