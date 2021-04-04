#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	pid_t pid;

	if ((pid = fork()) == -1) {
		return EXIT_FAILURE;
	} else if (pid == 0) {
		fputs("I'm a zombie", stdout);
		exit(1);
	} else {
		sleep(200);
		printf("Zombie pid is: %lu\n", (unsigned long) pid);
	}
}
