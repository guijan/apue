#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int globvar = 6; /* external variable in initialized data */

static void err_sys(const char *const);

int
main(void)
{
	int var; /* automatic variable on the stack */
	pid_t pid;
	var = 88;

	printf("before vfork\n"); /* we don't flush stdio */

	if ((pid = fork()) < 0) {
		err_sys("vfork error");
	} else if (pid == 0) { /* child */
		globvar++; /* modify parent's variables */
		var++;
		_exit(0); /* child terminates */
	}

	/* parent continues here */
	if (printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,
	    var) < 0
	) err_sys("printf returned -1");
	exit(EXIT_SUCCESS);
}

static void
err_sys(const char *const msg)
{
	if (errno)
		perror(NULL);
	fputs(msg, stderr);
	exit(EXIT_FAILURE);
}
