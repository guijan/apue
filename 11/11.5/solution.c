#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
	pthread_mutex_t lock;
	pthread_cond_t cond;
	unsigned int count;
	unsigned int req;
} my_barrier_t;

int
my_barrier_wait(my_barrier_t *bar)
{
	pthread_mutex_lock(&bar->lock);
	if (++bar->count >= bar->req) {
		bar->count = 0;
		pthread_cond_broadcast(&bar->cond);
		pthread_mutex_unlock(&bar->lock);
		return (PTHREAD_BARRIER_SERIAL_THREAD);
	}

	pthread_cond_wait(&bar->cond, &bar->lock);
	pthread_mutex_unlock(&bar->lock);
	return (0);
}

int
my_barrier_init(my_barrier_t *bar, pthread_barrierattr_t *attr,
		unsigned int req)
{
	if (attr != NULL)
		return (ENOTSUP);
	if (req == 0)
		return (EINVAL);
	if (bar == NULL)
		return (EINVAL);

	bar->lock = PTHREAD_MUTEX_INITIALIZER;
	bar->cond = PTHREAD_COND_INITIALIZER;
	bar->count = 0;
	bar->req = req;

	return (0);
}

int
my_barrier_destroy(my_barrier_t *bar)
{
	pthread_mutex_lock(&bar->lock);
	if (bar->count > 0)
		goto err;

	pthread_mutex_unlock(&bar->lock);
	pthread_mutex_destroy(&bar->lock);
	pthread_cond_destroy(&bar->cond);

	free(bar);
	return (0);
err:
	return (EBUSY);
}
