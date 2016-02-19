/*
	prog.c

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

#define SHELL_PATH_STRING "SHELL_PATH"

int main(int argc, char **argv, char** envp) {

	char* shellPath;

	for (char** env = envp; *env != NULL; env++) {
		char* thisEnv = *env;
		printf("%s\n", thisEnv);

		shellPath = strstr(thisEnv, SHELL_PATH_STRING);
	}

	if (shellPath == NULL) {
		printf("%s value is UNKNOWN.\n", SHELL_PATH_STRING);
	} else {
		printf("%s value is %s\n", SHELL_PATH_STRING, shellPath);
	}

	return 0;
}