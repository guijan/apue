#if defined(__FreeBSD__) || defined(__NetBSD__) ||	\
    defined(__OpenBSD__) || defined(__DragonFly__)
	/* We will also be using __BSD_VISIBLE to test for features common
	 * to all the BSDs.
	 */
	#define __BSD_VISIBLE 1
#else
	#define _XOPEN_SOURCE 700
#endif

#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <netdb.h>

#include "posixquirk.h"
#define logerrno() syslog(LOG_ERR, "%m")

#define PROGNAME ("rprocsd")
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static int daemonize(const char *);
static void closeallfds(void);
static int get_OPEN_MAX(void);
static size_t getproccount(void);
static int server(char **);

/* This program is a daemon. No perror() calls, only syslog() calls */
int
main(int argc, char **argv)
{
	int ret = EXIT_FAILURE;

	openlog(PROGNAME, 0, LOG_DAEMON);
	if (argc < 2) {
		syslog(LOG_ERR, "not enough args");
		goto err;
	} else if (argc > 2) {
		syslog(LOG_WARNING, "too many args");
	}

	if (daemonize(PROGNAME) == -1)
		goto err;

	if (server(argv) == -1)
		goto err;

	ret = EXIT_SUCCESS;
err:
	closelog();
	return (ret);
}

/* daemonize: do all the work necessary to daemonize
 *
 * sets errno and returns -1 on error
 */
static int
daemonize(const char *msg)
{
	pid_t pid;

	umask(0);

	if ((pid = fork()) == -1)
		goto err;
	else if (pid > 0)
		exit(EXIT_SUCCESS);

	if (setsid() == -1)
		goto err;

	if ((pid = fork()) == -1)
		goto err;
	else if (pid > 0)
		exit(EXIT_SUCCESS);

	if (chdir("/") == -1)
		goto err;

	closeallfds();

	return (0);
err:
	logerrno();
	return (-1);
}

/* closeallfds: do our best at closing all file descriptors
 *
 * Returns -1 on error.
 */
#if defined(__BSD_VISIBLE)
/*
 * Guaranteed to close all FDs.
 */
static void closeallfds(void)
{
	while (closefrom(0) == -1 && errno == EINTR)
		;
}
#else
/*
 * Not guaranteed to close all FDs. It's not possible to close all FDs in
 * POSIX.
 */
static void closeallfds(void)
{
	int i;
	const int open_max = get_OPEN_MAX();

	for (i = 0; i < open_max; i++)
		close_r(i);
}
#endif /* defined(__BSD_VISIBLE) */

/* get_OPEN_MAX: return a best guess at the platform's OPEN_MAX
 *
 * Does not fail, but is not guaranteed to be correct. Being unable to tell
 * the maximum FD is an issue with POSIX, not this software or function, but
 * shouldn't pose a problem in practice.
 */
static int
get_OPEN_MAX(void)
{
	struct rlimit rl = {0};
	int ret;

	(void)getrlimit(RLIMIT_NOFILE, &rl);
	if (rl.rlim_cur == RLIM_INFINITY || rl.rlim_cur == RLIM_SAVED_CUR)
		rl.rlim_cur = 0;
	if (rl.rlim_cur > 0)
		return (rl.rlim_cur);

	if ((ret = sysconf(_SC_OPEN_MAX)) != -1)
		return (ret);

#if !defined(OPEN_MAX)
	#define OPEN_MAX _POSIX_OPEN_MAX
#endif
	return (OPEN_MAX);
}

static size_t
getproccount(void)
{
	FILE *fp;
	size_t nr;
	unsigned char buf[BUFSIZ];
	size_t i;
	size_t nlcnt;
	int ret;

	if ((fp = popen("ps -Ao pid ", "r")) == NULL)
		goto err;

	/*
	 * nlcnt starts at -1 because ps(1)'s output has a header.
	 * XXX: nlcnt is initialized here and not inside the for loop to
	 * avoid a false compiler warning.
	 */
	nlcnt = -1;
	while ((nr = fread(buf, 1, sizeof(buf), fp)) > 0) {
		for (i = 0; buf[i] != 0 && i < nr; i++)
			if (buf[i] == '\n')
				nlcnt++;
	} if (feof(fp) != 0) {
		/* do nothing */
	} else if (ferror(fp) != 0) {
		goto err;
	} else {
		goto err;
	}

	while ((ret = pclose(fp)) == -1 && errno == EINTR)
		;
	if (ret == -1)
		goto err;

	return (nlcnt);
err:
	return (-1);
}

static int
server(char **argv)
{
	const struct addrinfo *aip;
	struct addrinfo *res0;
	struct addrinfo hints = {0};
	int fd;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_CANONNAME | AI_PASSIVE;

	if (getaddrinfo(argv[0], argv[1], &hints, &res0) < 0)
		goto err;
err:
	return (-1);
}
