#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 80

int main() {

	char input[MAX_INPUT_LENGTH];

	while (1) {
		printf("> ");
		scanf("%s", input);

		printf("the input is: %s", input);
	}

	return 0;
}