#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int
main(void)
{
	int i;
	struct tm *tmp;
	time_t epoch;
	FILE *fp;

	if ((fp = fopen("output.txt", "wb")) == NULL)
		goto err;

	for (i = 0;; i++) {
		sleep(60);
		i %= 5;
		if (i == 0) {
			if ((epoch = time(NULL)) == (time_t)-1 &&
			    errno == EFAULT
			) goto err;
			if ((tmp = localtime(&epoch)) == NULL)
				goto err;
			if (fprintf(fp, "%d\n", tmp->tm_sec) < 0)
				goto err;
		}
	}
err:
	return (EXIT_FAILURE);
}
