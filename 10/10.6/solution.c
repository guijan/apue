#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define RWXA S_IRWXU | S_IRWXG | S_IRWXO

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void err_sys(char *);

static void
sig_usr(int signo) /* one signal handler for SIGUSR1 and SIGUSR2 */
{
	sigflag = 1;
}

void
TELL_WAIT(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR1) error");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR2) error");
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);

	/* Block SIGUSR1 and SIGUSR2, and save current signal mask */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		err_sys("SIG_BLOCK error");
}

void
TELL_PARENT(pid_t pid)
{
	kill(pid, SIGUSR2);
}

void
WAIT_PARENT(void)
{
	while (sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 0;

	/* Reset signal mask to original value */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
}

void
TELL_CHILD(pid_t pid)
{
	kill(pid, SIGUSR1); /* tell child we're done */
}

void
WAIT_CHILD(void)
{
	while (sigflag == 0)
			sigsuspend(&zeromask); /* and wait for child */
	sigflag = 0;
	/* Reset signal mask to original value */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("SIG_SETMASK error");
}

static void
err_sys(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

/*
 *
 *
 *
 *
 *
 */

int
main(void)
{
	int fd;
	size_t nr;
	int numb;
	pid_t pid;

	if ((fd = open("binaryout", O_RDWR | O_CREAT | O_TRUNC, RWXA)) == -1)
		goto err;

	if ((pid = fork()) == -1) {
		goto err;
	} else if (pid == 0) {
		pid = getppid();
		for (;;) {
			WAIT_PARENT();

			if (lseek(fd, 0, SEEK_SET) == -1)
				goto err;
			if ((nr = read(fd, &numb, sizeof(numb))) == -1 ||
			    nr == 0
			) goto err;
			if (printf("numb VALUE: %d (CHILD)\n", numb) < 0)
				goto err;
			numb++;
			if (write(fd, &numb, sizeof(numb)) == -1)
				goto err;
			TELL_PARENT(pid);
		}
	} else {
		numb = 0;
		if (write(fd, &numb, sizeof(numb)) == -1)
			goto err;
		for (;;) {
			if (lseek(fd, 0, SEEK_SET) == -1)
				goto err;
			if ((nr = read(fd, &numb, sizeof(numb))) == -1 ||
			    nr == 0
			) goto err;
			if (printf("numb VALUE: %d (PARENT)\n", numb) < 0)
				goto err;
			numb++;
			if (write(fd, &numb, sizeof(numb)) == -1)
				goto err;
			TELL_CHILD(pid);
			WAIT_CHILD();
		}

	}

	return 0;
err:
	printf("WE FAILED %lu", (unsigned long)getpid());
	return -1;
}
