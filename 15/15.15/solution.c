#define XOPEN_SOURCE 700

#include <sys/shm.h>

#include <errno.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NEGNULL ((void *)-1) /* shmat returns (void *)-1 on error */
#define NLOOPS 1000

struct locklong {
	pthread_mutex_t mutex;
	long num;
};

int main(void);
static int update(long *);
void err_quit(char *msg, ...);

#ifdef __OpenBSD__
/* A stub because OpenBSD doesn't have this function */
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
#endif

int
main(void)
{
	int shmid;
	struct locklong *llp;
	pthread_mutexattr_t attr;
	pid_t pid;
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	int i;
	int counter;


	shmid = shmget(IPC_PRIVATE, sizeof(struct locklong), 0700);
	if (shmid == -1)
		goto err;

	if ((llp = (shmat(shmid, NULL, 0))) == NEGNULL)
		goto err;

	if ((errno = pthread_mutexattr_init(&attr)) < 0)
		goto err;
	errno = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
	if (errno < 0)
		goto err;
	if ((errno = pthread_mutex_init(&llp->mutex, &attr)) < 0)
		goto err;
	llp->num = 0;

	if ((pid = fork()) == -1) {
		goto err;
	} else if (pid > 0) {
		for (i = 0; i < NLOOPS; i += 2) {
			pthread_mutex_lock(&llp->mutex);
			if ((counter = update(&llp->num)) != i)
				err_quit("parent: expected %d, got %d\n",
					i, counter);
			pthread_mutex_unlock(&llp->mutex);
			pthread_cond_signal(&cond);
		}
	} else {
		for (i = 1; i < NLOOPS; i += 2) {
			pthread_cond_wait(&cond, &llp->mutex);
			if ((counter = update(&llp->num)) != i)
				err_quit(" child: expected %d, got %d\n",
					i, counter);
			pthread_mutex_unlock(&llp->mutex);
		}
	}
	return (EXIT_SUCCESS);
err:
	perror(NULL);
	return (EXIT_FAILURE);
}

static int
update(long *ptr)
{
	return ((*ptr)++);
}

void
err_quit(char *msg, ...)
{
	va_list ap;
	if (msg != NULL) {
		va_start(ap, msg);
		(void)vfprintf(stderr, msg, ap);
		va_end(ap);
	}
	perror(NULL);
	exit(EXIT_FAILURE);
}
