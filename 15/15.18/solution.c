#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

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
	sem_t sem;

	if ((fd = open("/dev/zero", O_RDWR)) < 0)
		err_sys("open error");
	if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
	  fd, 0)) == MAP_FAILED)
		err_sys("mmap error");
	close(fd);		/* can close /dev/zero now that it's mapped */
	if (sem_init(&sem, 1, 0) == -1)
		err_sys("sem_init failed");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {			/* parent */
		for (i = 0; i < NLOOPS; i += 2) {
			if ((counter = update((long *)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);

			if (sem_post(&sem) == -1)
				err_sys("parent sem_post error");
			if (sem_wait(&sem) == -1)
				err_sys("parent sem_wait error");
		}
	} else {						/* child */
		for (i = 1; i < NLOOPS + 1; i += 2) {
			if (sem_wait(&sem) == -1)
				err_sys("child sem_wait error");

			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);

			if (sem_post(&sem) == -1)
				err_sys("child sem_post error");
		}
	}

	exit(0);
}
