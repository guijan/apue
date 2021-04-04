#define _POSIX_C_SOURCE 200809L

#include <sys/socket.h>
#include <sys/types.h>

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>

#include "posixquirk.h"

#define PORT "5000"

static const char *PROGNAME;

const char *getproccount(const char *, const char *);

int
main(int argc, char **argv)
{
	PROGNAME = *argv++;
	const char *pc;

	for (; *argv; argv++) {
		if (fprintf(stdout, "%s: ", *argv) < 0)
			goto err;
		if ((pc = getproccount(*argv, PORT)) == NULL) {
			if (errno != 0) {
				if (fprintf(stdout,
				    "error, errno: %s\n", strerror(errno))
				    < 0)
					goto err;
			} else {
				if (fprintf(stdout,
				    "error, gai_strerror: %s\n",
				    gai_strerror(gaierrno))
				    < 0)
					goto err;
			}
		} else {
			if (fprintf(stdout, "%s\n", pc) < 0)
				goto err;;
		}
	}

	return (EXIT_SUCCESS);
err:
	if (errno > 0)
		perror(PROGNAME);
	if (gaierrno > 0)
		pgaierror(PROGNAME);
	return (EXIT_FAILURE);
}

/* getproccount: get proccess count from the host
 *
 * returns NULL on error.
 * Sets one of errno and gaierrno to 0 and the other to a non-0 value on
 * error.
 */
const char *
getproccount(const char *host, const char *port)
{
	struct addrinfo hints = {0};
	struct addrinfo *res;
	struct addrinfo *res0;
	/* set to invalid descriptor to avoid closing uninitialized value */
	int sd = -1;
	int err;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_CANONNAME;
	if (getaddrinfo_e(host, port, &hints, &res0) == -1) {
		errno = 0;
		return (NULL);
	}

	for (res = res0; res != NULL; res = res->ai_next) {
		sd = socket(res->ai_family, res->ai_socktype,
		    res->ai_protocol);
		if (sd == -1)
			continue;
	}

err:
	err = errno;
	close_r(sd);
	errno = err;
	return (NULL);
}

/* connect_r: connect() which may survive interrupts and has a timeout
 *
 * timeout is in seconds, set it to -1 for infinity or 0 for immediate return.
 * No attempt at making the timeout precise was made.
 * Setting timeout to 0 is not recommended, if the connection isn't ready
 * between the interrupt and the time poll() is called, then this function
 * will not recover from the interrupt.
 *
 * returns -1 on error
 */
int
connect_r(int timeout, int s, const struct sockaddr *name, socklen_t namelen)
{
	int ret;
	int flags;
	struct pollfd fds = {s, POLLOUT};

	if ((ret = flags = fcntl(s, F_GETFL)) == -1)
		goto end;
	if ((ret = fcntl(s, F_SETFL, flags | O_NONBLOCK) == -1))
		goto end;

	ret = connect(s, name, namelen);
	if (ret == -1 && errno != EINPROGRESS && errno != EINTR)
		goto end;

	if (poll(&fds, 1, timeout) == -1) {
		goto end;
	} else if (ret == 0) {
		/*
		 * poll() does not consider timing out an error, but it is
		 * an error for us. Set errno to ETIMEDOUT.
		 */
		errno = ETIMEDOUT;
		goto end;
	}

	ret = 0;
end:
	fcntl(s, F_SETFL, flags);
	return (ret);
}
