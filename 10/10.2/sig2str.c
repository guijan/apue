/* sig2str for OpenBSD */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define NUMSIG 32 /* Number of signals supported by OpenBSD */

const static char *const signals[/* const */] = {
	"NULL", /* 0, the null signal. Unused. */

	/* Signal list from /usr/include/sys/signal.h */
	"HUP",
	"INT",
	"QUIT",
	"ILL",
	"TRAP",
	"ABRT",
	"EMT",
	"FPE",
	"KILL",
	"BUS",
	"SEGV",
	"SYS",
	"PIPE",
	"ALRM",
	"TERM",
	"URG",
	"STOP",
	"TSTP",
	"CONT",
	"CHLD",
	"TTIN",
	"TTOU",
	"IO",
	"XCPU",
	"XFSZ",
	"VTALRM",
	"PROF",
	"WINCH",
	"INFO",
	"USR1",
	"USR2",
	"THR",
	NULL,
};

static int numstr2sig(const char *, int *);
static int texstr2sig(const char *, int *);

/* sig2str: sig2str from Solaris */
int
sig2str(int signo, char *str)
{
	if (signo <= NUMSIG && signo > 0) {
		memcpy(str, signals[signo], sizeof(*signals[signo]));
		return 0;
	}
	return -1;
}

/* str2sig: str2sig from Solaris */
int
str2sig(const char *str, int *signop)
{
	if (isdigit(*str))
		return numstr2sig(str, signop);

	return texstr2sig(str, signop);
}

/* numstr2sig: numeric string to signal
 *
 * str is the numeric string to convert.
 * signop is the resulting integer representing the signal.
 *
 * return 0 on success.
 * return -1 on signal number out of range.
 */
static int
numstr2sig(const char *str, int *signop)
{
	long signo;
	char *ep;

	errno = 0;
	signo = (strtol(str, &ep, 10));
	if ((str[0] == 0 || *ep != 0) ||
	    (errno = ERANGE && (signo == LONG_MAX || signo == LONG_MIN)) ||
	    (signo > NUMSIG || signo <= 0)
	) return -1;

	*signop = signo;
	return 0;
}

/* texstr2sig: (text) string to signal
 *
 * str is the string to convert. It is in the form of a signal name minus the
 * "SIG".
 * signop is the resulting integer representing the signal.
 *
 * return 0 on success.
 * return -1 on string not found.
 */
static int
texstr2sig(const char *str, int *signop)
{
	const char *const *i;

	for (i = signals + 1; *i; i++)
		if (!strcmp(*i, *signals))
			break;

	*signop = i - signals;
	return ((*signop <= NUMSIG) - 1);
}
