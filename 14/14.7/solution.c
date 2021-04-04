#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

unsigned long ulpow(unsigned long x, unsigned long y);

int
main(void)
{
	int i;
	size_t size;
	ssize_t rc;
	void *buf;
	void *retbuf;
	int rval = EXIT_FAILURE;

	if ((buf = (malloc(1))) == NULL)
		goto end;
	if (fcntl(STDOUT_FILENO, O_NONBLOCK) == -1)
		goto end;
	for (i = 1, size = 2; (size = ulpow(size, i)) > 0; i++) {
		if ((retbuf = realloc(buf, size)) == NULL) {
			goto end;
		} else {
			buf = retbuf;
			memset(buf, 0, size);
		}
		if ((rc = write(STDOUT_FILENO, buf, size)) == -1) {
			if (errno == EAGAIN)
				break;
			goto end;
		}
	}

	if (size == 0 && errno == EOVERFLOW)
		goto end;

	fprintf(stderr, "size which couldn't block: %lu",
	    (unsigned long)size);
	rval = EXIT_SUCCESS;
end:
	free(buf);
	perror(NULL);
	return (rval);
}

unsigned long
ulpow(unsigned long x, unsigned long y)
{
	long pow;
	const long oflw = LONG_MAX / x;

	pow = x;
	while (y--) {
		if (pow > oflw) {
			errno = EOVERFLOW;
			return (0);
		}
		pow *= x;
	}
	return (pow);
}
