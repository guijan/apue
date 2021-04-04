#define _POSIX_C_SOURCE 200809L

#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <poll.h>

#define BUFLEN	128
#define QLEN 10
#define NFDS 16

#ifndef HOST_NAME_MAX
	#define HOST_NAME_MAX 256
#endif

struct pollfdbuf {
	struct pollfd *fds;
	/* How many members are in the buffer pointed to by *fds. */
	nfds_t nfds;
	/* How many members fit in the buffer pointed to by *fds. */
	size_t bufmemb;
};

void err_quit(const char *, ...);
void err_sys(const char *, ...);
void daemonize(const char *);
int multiendinit(const struct addrinfo *);
int initserver(int, const struct sockaddr *, socklen_t, int);
int pollserve(const struct pollfdbuf *);
void serve(int);
int set_cloexec(int);

int
main(int argc, char *argv[])
{
	struct addrinfo	*ailist;
	struct addrinfo	hint;
	int err, n;
	char *host;

	if (argc != 1)
		err_quit("usage: ruptimed");
	if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
		n = HOST_NAME_MAX;	/* best guess */
	if ((host = malloc(n)) == NULL)
		err_sys("malloc error");
	if (gethostname(host, n) < 0)
		err_sys("gethostname error");
	daemonize("ruptimed");
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
		  gai_strerror(err));
		exit(1);
	}
	if ((multiendinit(ailist)) == -1)
		exit(1);
	exit(1);
}

void
err_quit(const char *msg, ...)
{
	va_list ap;
	if (msg != NULL)
		(void)fprintf(stderr, "%s: ", msg);

	va_start(ap, msg);
	(void)vfprintf(stderr, msg, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void
daemonize(const char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	/*
	 * Clear file creation mask.
	 */
	umask(0);

	/*
	 * Get maximum number of file descriptors.
	 */
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		err_quit("%s: can't get file limit", cmd);

	/*
	 * Become a session leader to lose controlling TTY.
	 */
	if ((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if (pid != 0) /* parent */
		exit(0);
	setsid();

	/*
	 * Ensure future opens won't allocate controlling TTYs.
	 */
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: can't ignore SIGHUP", cmd);
	if ((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if (pid != 0) /* parent */
		exit(0);

	/*
	 * Change the current working directory to the root so
	 * we won't prevent file systems from being unmounted.
	 */
	if (chdir("/") < 0)
		err_quit("%s: can't change directory to /", cmd);

	/*
	 * Close all open file descriptors.
	 */
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	/*
	 * Attach file descriptors 0, 1, and 2 to /dev/null.
	 */
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	/*
	 * Initialize the log file.
	 */
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d",
		  fd0, fd1, fd2);
		exit(1);
	}
}

int
multiendinit(const struct addrinfo *ainfo)
{
	struct pollfdbuf nfdsbuf;
	const struct addrinfo *aip;
	void *tmp;

	nfdsbuf.bufmemb = NFDS;
	if ((nfdsbuf.fds = malloc(nfdsbuf.bufmemb * sizeof(*nfdsbuf.fds)))
	    == NULL) goto err;

	for (nfdsbuf.nfds = 0, aip = ainfo;
	    aip != NULL;
	    nfdsbuf.nfds++, aip = aip->ai_next
	    ) {
		if (nfdsbuf.bufmemb == nfdsbuf.nfds) {
			nfdsbuf.bufmemb <<= 1;
			if (nfdsbuf.nfds > nfdsbuf.bufmemb)
				goto err;
			tmp = realloc(nfdsbuf.fds,
			    nfdsbuf.bufmemb * sizeof(*nfdsbuf.fds));
			if (tmp == NULL)
				goto err;
			nfdsbuf.fds = tmp;
		}
		if ((nfdsbuf.fds[nfdsbuf.nfds].fd =
		    initserver(aip->ai_socktype, aip->ai_addr,
		        aip->ai_addrlen, QLEN))
		    == -1) goto err;
	}

	if (pollserve(&nfdsbuf) == -1)
		goto err;

	return (0);
err:
	free(nfdsbuf.fds);
	return (-1);
}

int
initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
	int fd, err;
	int reuse = 1;

	if ((fd = socket(addr->sa_family,type,0)) < 0)
		return (-1);
	if ((setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)))
	    < 0)
		goto errout;
	if (bind(fd, addr, alen) < 0)
		goto errout;

	if (type == SOCK_STREAM || type == SOCK_SEQPACKET)
		if (listen(fd, qlen) < 0)
			goto errout;
	return (fd);
errout:
	err = errno;
	close(fd);
	errno = err;
	return (-1);
}

int
pollserve(const struct pollfdbuf *pbfds)
{
	int pc;
	size_t i;

	for (i = 0; i < pbfds->nfds; i++) {
		pbfds->fds[i].events = POLLIN | POLLOUT | POLLERR;
	}

	while ((pc = poll(pbfds->fds, pbfds->nfds, -1)) != -1 ||
	    errno == EINTR) {
		for (i = 0; i < pc; pc--) {
			if (pbfds->fds[i].revents | POLLIN | POLLOUT) {
				serve(pbfds->fds[i].fd);
			}
			if (pbfds->fds[i].revents | POLLERR)
				break;
		}
	}

	return (-1);
}

void
serve(int sockfd)
{
	int	clfd;
	FILE	*fp;
	char	buf[BUFLEN];

	set_cloexec(sockfd);
	for (;;) {
		if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
			syslog(LOG_ERR, "ruptimed: accept error: %s",
			  strerror(errno));
			exit(1);
		}
		set_cloexec(clfd);
		if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
			sprintf(buf, "error: %s\n", strerror(errno));
			send(clfd, buf, strlen(buf), 0);
		} else {
			while (fgets(buf, BUFLEN, fp) != NULL)
				send(clfd, buf, strlen(buf), 0);
			pclose(fp);
		}
		close(clfd);
	}
}

int
set_cloexec(int fd)
{
	int val;

	if ((val = fcntl(fd, F_GETFD, 0)) < 0)
		return (-1);
	val |= FD_CLOEXEC;

	return (fcntl(fd, F_SETFD, val));

}
