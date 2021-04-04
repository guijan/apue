#include "posixquirk.h"

int
close_r(int fd)
{
	int ret;

	while ((ret = close(fd)) == -1 && errno == EINTR)
		;

	return (ret);
}
