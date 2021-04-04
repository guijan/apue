#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int
main(void)
{
	pid_t pid;
	FILE *ofile;
	char msg[] = "We don't have a controlling terminal "
	    "and we're the group leader\n";
	size_t msglen = strlen(msg);

	if ((pid = fork()) == -1)
		goto err;
	else if (pid > 0)
		return EXIT_SUCCESS;

	if ((ofile = fopen("out.txt", "ab")) == NULL)
		goto err;

	if ((pid = setsid()) == -1)
		goto err;

	if (getpgrp() != pid)
		return EXIT_FAILURE;

	if (tcgetsid(STDIN_FILENO) != -1 && errno != ENOTTY)
		return EXIT_FAILURE;

	if (fwrite(msg, msglen, 1, ofile) != msglen)
		goto err;

	return EXIT_SUCCESS;
err:
	perror(NULL);
	return EXIT_FAILURE;
}
