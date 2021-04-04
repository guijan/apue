#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int
main(void)
{
	time_t unixtime = INT_MAX;
	const char *sdate;

	sdate = ctime(&unixtime);

	if (printf("%s", sdate) < 0)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
