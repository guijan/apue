#define _POSIX_C_SOURCE 200809L

#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int
main(void)
{
	time_t curtime;
	char *curtimebuf;
	errno = 0;
	if ((curtime = time(NULL)) == (time_t)-1)
		if (errno == EOVERFLOW)
			goto err;

	if ((curtimebuf = (malloc(26))) == NULL)
		goto err;

	printf("current time: %s", ctime_r(&curtime, curtimebuf));
	printf("overflow time: %s", ctime_r(&curtime, curtimebuf));

	free(curtimebuf);
err:
	if (errno)
		perror(NULL);
	return (EXIT_FAILURE);
}
