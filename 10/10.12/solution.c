#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define GB (1024 * 1024 * 1024)

void sig_alrm(int);

int
main(void)
{
	void *buf;
	FILE *fp;
	const size_t fplen = GB;
	int retval = EXIT_FAILURE;
	struct sigaction act;

	if ((buf = calloc(fplen, 1)) == NULL)
		goto end;
	if ((fp = fopen("test", "wb")) == NULL)
		goto end;
	if (setvbuf(fp, buf, _IOFBF, fplen))
		goto end;

	act.sa_handler = &sig_alrm;
	if (sigemptyset(&act.sa_mask) == -1)
		goto end;
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGALRM, &act, NULL) == -1)
		goto end;
	alarm(1);
	if (fwrite(buf, fplen, 1, fp) != fplen)
		goto end;

	retval = EXIT_SUCCESS;
end:
	free(buf);
	return (retval);
}

void
sig_alrm(int signo)
{
	printf("%s\n", "SIGALRM CAUGHT");
}
