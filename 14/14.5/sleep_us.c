#include <time.h>
#include <sys/select.h>

int
sleep_us(time_t sleep)
{
	struct timeval time;

	if (sleep == 0)
		return (0);

	time.tv_sec = 0;
	time.tv_usec = sleep;
	return (select(0, NULL, NULL, NULL, &time));
}
