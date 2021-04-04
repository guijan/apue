/* A solution for exercise 4.6 of the book "Advanced Programming in the UNIX
 * environment, 3rd edition"
 */
#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define RWRWRW S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

char *progname;

static void err(const char *const msg);
static void ret_err(const char *const msg);
static int copy(const int, const int);
int testzero(const void *const, size_t);

int
main(int argc, char **argv)
{
	int fdin;
	int fdout;
	progname = *argv;

	if (argc != 3)
		err("usage: infile outfile");
	argv++, argc--;

	if ((fdin = open((argc--, *argv++), O_RDONLY)) == -1)
		err(NULL);
	if (
	    (fdout = open((argc--, *argv), O_WRONLY | O_TRUNC | O_CREAT,
	        RWRWRW)
	    )
	    == -1
	) err(NULL);

	if (copy(fdin, fdout)) {
		ret_err(NULL);
		if (unlink(*argv) == -1)
			ret_err(NULL);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}

/* err: error exit.
 *
 * If msg is NULL, print error message associated with errno, otherwise print
 * msg.
 */
static void
err(const char *const msg)
{
	ret_err(msg);
	exit(EXIT_FAILURE);
}

/* ret_err: print errno error.
 *
 * If msg is NULL, print error message associated with errno, otherwise print
 * msg.
 */
static void
ret_err(const char *const msg)
{
	(void)fprintf(stderr,
	    "%s: %s\n",
	    progname, msg == NULL ? strerror(errno) : msg
	);
}

/* copy: copy fdin to fdout, make a sparse file if fdin is sparse */
static int
copy(const int fdin, const int fdout)
{
	unsigned char *buf;
	ssize_t bufsz = BUFSIZ;
	ssize_t rval = -1;
	ssize_t wn; /* only here to be tested against rval after write(3) */
	if ((buf = malloc(bufsz)) == NULL)
		return rval;

	while((rval = read(fdin, buf, bufsz)) != -1 && rval) {
		if (testzero(buf, rval) == 0) {
			if ((rval = lseek(fdout, rval, SEEK_CUR)) == -1)
				break;
			else
				continue;
		}
		if ((wn = write(fdout, buf, rval)) != rval) {
			rval = wn;
			errno = EIO;
			break;
		}
	}

	free(buf);
	return rval;
}

/* testzero: return 0 if the buffer is zeroed */
int
testzero(const void *const buf, size_t size)
{
	const unsigned char *byte = buf;
	for (; size; size--, byte++)
		if (*byte)
			break;
	return *byte;
}
