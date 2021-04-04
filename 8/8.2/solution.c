#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int forktest(void);

int
main(void)
{
	if (forktest())
		return EXIT_FAILURE;

	fputs("we succeeded", stdout);
}

int
forktest(void)
{
	pid_t pid;

	if ((pid = vfork()) < 0) {
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		fputs("we succeeded", stdout);
		return(EXIT_FAILURE);
	}
	fputs("we succeeded", stdout);
	return 0;
}
