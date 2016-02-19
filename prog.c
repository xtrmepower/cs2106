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

int main(int argc, char **argv, char** envp) {
	
	for (char** env = envp; *env != NULL; env++) {
		char* thisEnv = *env;
		printf("%s\n", thisEnv);
	}

	return 0;
}