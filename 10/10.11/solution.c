#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

#define	BUFFSIZE 100

void err_sys(char *);
void sig_xfsz(int);

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];
	struct sigaction act;
	struct rlimit lim;
	ssize_t ret;

	lim.rlim_cur = 1024;
	lim.rlim_max = 1024;
	if (setrlimit(RLIMIT_FSIZE, &lim) == -1)
		goto err;

	act.sa_handler = &sig_xfsz;
	if (sigemptyset(&act.sa_mask) == -1)
		goto err;
	act.sa_flags = 0;

	if (sigaction(SIGXFSZ, &act, NULL) == -1)
		goto err;

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		if ((ret = write(STDOUT_FILENO, buf, n)) != n) {
			fprintf(stderr,
			    "write error, "
			    "bytes written: %ld "
			    "correct size: %d\n",
			    ret, n
			);
		}
	}

	if (n < 0)
		err_sys("read error");

err:
	exit(0);
}

void
err_sys(char *msg)
{
	if (msg)
		fputs(msg, stderr);
	/* exit(1); */
}

void
sig_xfsz(int signo)
{
	printf("%s\n", "SIGXFSZ CAUGHT");
}
