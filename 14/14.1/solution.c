#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#define RWXRWXRWX (S_IRWXU | S_IRWXG | S_IRWXO)
#define TRUNCLEN (1024 * 1024)

int testlck(time_t, int, short);
int selsleep(time_t);
int fcntllck(int, off_t, off_t, short, struct flock *);
int fcntlunl(int, struct flock *);

int
main(void)
{
	close(STDIN_FILENO);
	pid_t pid;
	int fd;
	int i;

#define OFLAGS (O_RDWR | O_CREAT | O_TRUNC)
	if ((fd = open("testfile.txt", OFLAGS, RWXRWXRWX)) == -1)
		goto err;
#undef OFLAGS
	if (ftruncate(fd, TRUNCLEN) == -1)
		goto err;

	if ((pid = fork()) == -1) {
		goto err;
	} else if (pid == 0) {
		sleep(1);
		testlck(8, fd, F_WRLCK);
	} else {
		if ((pid = fork()) == -1) {
			goto err;
		} else if (pid == 0) {
			for (i = 0; i < 8; i++)
				testlck(5, fd, F_RDLCK);
		} else {
			for (i = 0; i < 8; i++)
				testlck(8, fd, F_RDLCK);
		}
	}
	pause();
	return (EXIT_SUCCESS);
err:
	return (128 + errno);
}

int
testlck(time_t sleep, int fd, short l_type)
{
	struct timespec ts;
	struct flock lock = {0};
	char *msg;

	msg = l_type == F_WRLCK ? "WRLCK" : "RDLCK";
	fcntllck(fd, 0, SEEK_SET, F_RDLCK, &lock);
	clock_gettime(CLOCK_REALTIME, &ts);
	fprintf(stderr, "%s get time: %s", msg, ctime(&ts.tv_sec));

	selsleep(sleep);

	fcntlunl(fd, &lock);
	clock_gettime(CLOCK_REALTIME, &ts);
	fprintf(stderr, "%s del time: %s", msg, ctime(&ts.tv_sec));

	return (0);
}

int
selsleep(time_t sleep)
{
	struct timeval timeout;
	timeout.tv_usec = 0;
	timeout.tv_sec = sleep;
	return (select(0, NULL, NULL, NULL, &timeout));
}

int
fcntllck(int fd, off_t l_start, off_t l_len, short l_type, struct flock *flp)
{
	flp->l_start = l_start;
	flp->l_len = l_len;
	flp->l_type = l_type;
	flp->l_pid = getpid();
	return (fcntl(fd, F_SETLKW, flp));
}

int
fcntlunl(int fd, struct flock *flp)
{
	flp->l_type = F_UNLCK;
	return (fcntl(fd, F_SETLKW, flp));
}
