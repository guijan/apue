#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main(void)
{
	int pfd[2]; /* parent-to-child pipe */
	int cfd[2]; /* child-to-parent pipe */
	pid_t pid;
	fd_set fdset;

	if (pipe(pfd) == -1)
		goto err;
	if (pipe(cfd) == -1)
		goto err;

	if ((pid = fork()) == -1) {
		goto err;
	} else if (pid == 0) {
		close(pfd[1]);
		close(cfd[0]);

		close(pfd[0]);
		return (EXIT_SUCCESS);
	} else {

		close(pfd[0]);
		close(cfd[1]);
		sleep(5);

		FD_ZERO(&fdset);
		FD_SET(cfd[0], &fdset);
		if (select(1, NULL, &fdset, &fdset, NULL) == -1)
			goto err;
	}

	return (EXIT_SUCCESS);
err:
	perror(NULL);
	return (EXIT_FAILURE);
}
