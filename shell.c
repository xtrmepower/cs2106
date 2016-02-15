#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 80

int main(int argc, char *argv[], char *envp[]) {

	pid_t pid;
	char *const parmList[] = {"/bin/ls", "-l", "/tmp", NULL};

	if ((pid = fork()) > 0) {
		printf("Loading new process with pID %d\n", pid);
		printf("Parent pID: %d\n", getpid());
	}
	else if (pid == 0) {
		// in child
		execv("/bin/ls", parmList);
		printf("Return not expected. Must be an execv error.n");

		exit(0);
	} else {
		perror("fork error");
		exit(1);
	}

	printf("bye bye\n");

	exit(0);

	//char input[MAX_INPUT_LENGTH];

	//char *pch;

	//while (1) {
		/*printf("> ");
		scanf("%s", input);

		printf("input = %s\n", input);

		pch = strtok(input, " ,.-");

		printf("text (post-strtok) = %s\n", pch);



		int pid = 0;

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
		}*/

		//execv(input, );
	//}

	exit(0);
}