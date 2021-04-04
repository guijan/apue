#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define	NLOOPS		1000
#define	SIZE		sizeof(long)	/* size of shared memory area */

static int
update(long *ptr)
{
	return((*ptr)++);	/* return value before increment */
}

int
main(void)
{
	int		fd, i, counter;
	pid_t	pid;
	void	*area;
	int fd;
	struct flock lck;

	if ((fd = open("/dev/zero", O_RDWR)) < 0)
		err_sys("open error");
	if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
	  fd, 0)) == MAP_FAILED)
		err_sys("mmap error");
	close(fd);		/* can close /dev/zero now that it's mapped */

	if ((fd = open("test.txt", O_WRONLY | O_CREAT)) == -1)
		err_sys("open error");
	lck.l_start = 0;
	lck.l_len = 0;
	lck.l_pid = getpid();
	lck.l_type = F_WRLCK;
	lck.l_whence = SEEK_SET;
	if (fcntl(fd, F_SETLKW, &lck) == -1)
		err_sys("child fcntl error");
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {			/* parent */
		for (i = 0; i < NLOOPS; i += 2) {
			if ((counter = update((long *)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);

			lck.l_type = F_UNLCK;
			if (fcntl(fd, F_SETLKW, &lck) == -1)
				err_sys("child fcntl error");
			lck.l_type = F_WRLCK;
			if (fcntl(fd, F_SETLKW, &lck) == -1)
				err_sys("child fcntl error");
		}
	} else {						/* child */
		lck.l_pid = getpid();
		for (i = 1; i < NLOOPS + 1; i += 2) {
			lck.l_type = F_WRLCK;
			if (fcntl(fd, F_SETLKW, &lck) == -1)
				err_sys("child fcntl error");
			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);

			lck.l_type = F_UNLCK;
			if (fcntl(fd, F_SETLKW, &lck) == -1)
				err_sys("child fcntl error");
		}
	}

	exit(0);
}
