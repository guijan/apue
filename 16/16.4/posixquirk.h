#if !defined(POSIXQUIRK_H)
#define POSIXQUIRK_H

#include <sys/socket.h>

#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

int gaierrno;

/* close_r: close() but recovers from EINTR */
int close_r(int);

/* getaddrinfo_e: getaddrinfo() with errno-like functionality
 *
 * returns -1 on error.
 * returns 0 on success.
 * sets a valid gai_strerror() value to the variable gaierrno on error.
 */
#define getaddrinfo_e(a, b, c, d) 					\
	(-((gaierrno = (getaddrinfo((a), (b), (c), (d)))) != 0))

/* pgaierror: perror() for gaierrno */
#define pgaierror(a) do {						\
	if ((a) != NULL) {						\
		(void)fprintf(stderr, 					\
		    "%s: %s\n", (a), gai_strerror(gaierrno));		\
	} else {							\
		(void)fprintf(stderr, "%s\n", (a));			\
	}								\
} while (0)

#endif /* !defined(POSIXQUIRK_H) */
