#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

int
main(void)
{
	int pfd[2]; /* parent-to-child pipe */
	int cfd[2]; /* child-to-parent pipe */
	pid_t pid;
	struct pollfd pollfd;

	if (pipe(pfd) == -1)
		goto err;
	if (pipe(cfd) == -1)
		goto err;

	if ((pid = fork()) == -1) {
		goto err;
	} else if (pid == 0) {
		close(pfd[1]);
		close(cfd[0]);

		sleep(5);
		close(cfd[1]);
		return (EXIT_SUCCESS);
	} else {
		close(pfd[0]);
		close(cfd[1]);

		pollfd.fd = cfd[0];
		pollfd.events = POLLNVAL | POLLERR | POLLHUP | POLLIN;
		if (poll(&pollfd, 1, INFTIM) == -1)
			goto err;
		if (pollfd.revents & POLLNVAL)
			fprintf(stderr, "POLLNVAL set\n");
		if (pollfd.revents & POLLERR)
			fprintf(stderr, "POLLERR set\n");
		if (pollfd.revents & POLLHUP)
			fprintf(stderr, "POLLHUP set\n");
		if (pollfd.revents & POLLIN)
			fprintf(stderr, "POLLIN set\n");
	}

	return (EXIT_SUCCESS);
err:
	perror(NULL);
	return (EXIT_FAILURE);
}
