#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 80

int main(int argc, char *argv[]) {

	char input[MAX_INPUT_LENGTH];

	int pid;

	if ((pid = fork()) > 0) {
		// in parent
		printf("parent ID: %d \n forked child ID: %d \n", getpid(), pid);
	} else if (pid == 0) {
		// in child
		printf("child ID: %d\n", getpid());
	} else {
		// can't fork
		perror("fork demo");
		exit(1);
	}

	return 0;

	/*while (1) {
		printf("> ");
		scanf("%s", input);

		printf("the input is: %s", input);

		execv(input);
	}*/

	//return 0;
}