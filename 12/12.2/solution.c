#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

static pthread_mutex_t envlock = PTHREAD_MUTEX_INITIALIZER;
extern char **environ;

int
newputenv_r(char *str)
{
	int ret;
	sigset_t nset, oset;

	sigfillset(&nset);
	sigprocmask(SIG_SETMASK, &nset, &oset);
	pthread_mutex_lock(&envlock);
	ret = putenv(str);
	pthread_mutex_unlock(&envlock);
	sigprocmask(SIG_SETMASK, &oset, NULL);
	return ret;
}

/* putenv_r: async-signal-safe and thread-safe putenv
 * Its behavior is undefined if you manipulate environ directly or call
 * putenv.
 *
 * nenv is the new area to hold the environment, it must fit one more entry
 * than
 */
int
putenv_r(char **nenv, char *str)
{
	char *strstrt; /* start of str */
	char **nenvstrt; /* start of nenv */
	/* size of the name of the environment variable,
	 * excluding the = which terminates it.
	 */
	size_t namlen;

	if (str == NULL)
		return (EINVAL);
	if (nenv == NULL)
		return (ENOMEM);
	for (strstrt = str; *str != '='; str++)
		if (*str == 0)
			return (EINVAL);

	namlen = str - strstrt;

	pthread_mutex_lock(&envlock);
	for (nenvstrt = nenv; *environ; environ++, nenv++)
		if (!strncmp(strstrt, *environ, namlen)) {
			*environ = strstrt;
			return (0);
		} else {
			*nenv = *environ;
		}
	*nenv = strstrt;
	*++nenv = NULL;
	environ = nenvstrt;
	pthread_mutex_unlock(&envlock);
	return (0);
}

/* expandenv: return the size of environ expanded to fit count extra entries.
 */
size_t
expandenv(size_t count)
{
	char **envcpy = environ;

	while (envcpy)
		envcpy++;

	for (; count; count--)
		envcpy++;

	return ((envcpy - environ) * sizeof(char **));
}
