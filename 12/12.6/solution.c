#include <signal.h>
#include <unistd.h>
#include <pthread.h>

static pthread_mutex_t alrmmutex = PTHREAD_MUTEX_INITIALIZER;

static void
sig_alrm(int signo)
{
	/* nothing to do, just returning wakes up sigsuspend() */
}

unsigned int
sleep(unsigned int seconds)
{
	struct sigaction	newact, oldact;
	sigset_t		newmask, oldmask, suspmask;
	unsigned int		unslept;

	/* set our handler, save previous information */
	newact.sa_handler = sig_alrm;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	/* block SIGALRM and save current signal mask */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);

	pthread_mutex_lock(&alrmmutex);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);
	sigaction(SIGALRM, &newact, &oldact);

	alarm(seconds);
	suspmask = oldmask;

	/* make sure SIGALRM isn't blocked */
	sigdelset(&suspmask, SIGALRM);

	/* wait for any signal to be caught */
	sigsuspend(&suspmask);

	/* some signal has been caught, SIGALRM is now blocked */
	unslept = alarm(0);

	/* reset previous action */
	sigaction(SIGALRM, &oldact, NULL);

	/* reset signal mask, which unblocks SIGALRM */
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	pthread_mutex_unlock(&alrmmutex);
	return(unslept);
}
