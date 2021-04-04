/* For Advanced Programming in the UNIX Environment's exercise 3.2 */

#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int fakedup2(int oldd, int newd);

int
main(void)
{
	int oldd = STDERR_FILENO;
	int fd;
	char prtstr[] = "SUCCESS!";
	ssize_t prtstrlen = strnlen(prtstr, SSIZE_MAX);

	if ((fd = fakedup2(oldd, 8)) == -1)
		goto err;

	if ((write(fd, prtstr, prtstrlen)) != prtstrlen)
		goto err;

	exit(EXIT_SUCCESS);
err:
	exit(EXIT_FAILURE);
}


int
fakedup2(int oldd, int newd)
{
	assert(oldd >= 0 && newd >= 0);
	int rval = -1;
	int *fds;
	int i;

	if (oldd == newd)
		return oldd;
	if ((close(newd)) == -1 && errno != EBADF)
		return rval;

	/* We must allocate 1 more int than newd in case newd is 0 */
	if ((fds = calloc(newd + 1, sizeof(int))) == NULL)
			return rval;

	i = 0;
	do {
		if ((fds[i] = dup(oldd)) == -1)
			goto end;
	} while (fds[i] != newd && ++i < newd);

	if (fds[i] == newd)
		rval = newd;

	while (--i >= 0)
		if (close(fds[i]) == -1)
			rval = -1;
end:
	free(fds);
	return rval;
}
