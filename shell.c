/*
	shell.c

	CS2106 Introduction to Operating Systems
	AY2015/2016 SEM2
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

//#define PRINT_CHILD_EXIT_STATUS

/*	Compares the last character in target string against c,
 *	If same, return position of the last character in target string.
 *	Else, returns -1.
 */
int compareLastChar(char* target, char* c) {

	int lastCharPos = strlen(target) - 1;

	if (target[lastCharPos] == *c) {
		return lastCharPos;
	}

	return -1;
}

/*	Obtains input from the user.
 */
void getInput(char* input) {
	printf("> ");
	fgets(input, MAX_INPUT_LENGTH, stdin);
}

/*	Tokenizes the input string based on the delimiter string passed in.
 *	Returns an output array of strings.
 */
int tokenize(char* output[], char* input, char *delimiter) {
	char *pch = NULL;
	char *rest = input;
	int i = 0;

	while ((pch = strtok_r(rest, delimiter, &rest))) {
		output[i] = pch;
		i++;
	}

	return i;
}

/*	Will only be called by a child process.
 *	Runs the command that has been passed in.
 */
void runChildProcess(char** paramList) {
	char **pathLocationList;
	pathLocationList = malloc(MAX_PATH_LENGTH);

	// Get the path environment variable.
	char *pathVar = getenv("PATH");
	int numOfPathLocations = tokenize(pathLocationList, pathVar, ":");

	char cmd[MAX_INPUT_LENGTH];
	int lastCharPos = 0;

	// Try running the process from the local directory first.
	strcpy(cmd, "./");
	strcat(cmd, paramList[0]);
	execvp(cmd, paramList);

	// If it doesn't exist in the local directory 
	for (int i = 0; i < numOfPathLocations; i++) {
		strcpy(cmd, pathLocationList[i]);
		// check if last character is '/'
		lastCharPos = compareLastChar(cmd, "/");

		// If it is, append '/' to it.
		if (lastCharPos == -1) {
			strcat(cmd, "/");
		}
		
		// Run the command.
		strcat(cmd, paramList[0]);
		execvp(cmd, paramList);
	}
	perror("Shell error: ");

	free(pathLocationList);
}

int main(int argc, char *argv[], char *envp[]) {
	pid_t pid;

	// Loop forever!
	while (1) {
		char input[MAX_INPUT_LENGTH];
		getInput(input);

		// See if the last character is a newline character
		int result = compareLastChar(input, "\n");
		if (result != -1) {
			// If it is, replace it with a null terminator
			input[result] = '\0';
		}

		// Create a temporary memory space to store longest possible input.
		char **paramList;
		paramList = malloc(MAX_INPUT_LENGTH);

		// Tokenize the input and resize its allocated memory space.
		int numOfParam = tokenize(paramList, input, " ");
		realloc(paramList, numOfParam+1);
		paramList[numOfParam] = NULL;

		// Create a new child process.
		if ((pid = fork()) > 0) {
			printf("Loading new process with pID %d\n", pid);
			printf("Parent pID: %d\n", getpid());

			#ifdef PRINT_CHILD_EXIT_STATUS
			int status;
			wait(&status);

			if (WIFEXITED(status)) {
				printf("Child exited with status: %d \n", WEXITSTATUS(status));
			}
			#else
			wait(NULL);
			#endif

			printf("\n");
		} else if (pid == 0) {
			// in child, run child's process
			runChildProcess(paramList);
			exit(0);
		} else {
			perror("Error in forking");
			exit(1);
		}
		free(paramList);
	}
	exit(0);
}