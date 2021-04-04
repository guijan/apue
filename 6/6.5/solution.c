#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define TIME_MAX ((time_t)-1)
#define DATESIZE 512

int
main(void)
{
	time_t tloc;
	struct tm *tmloc;
	char strdate[DATESIZE];
	errno = 0;
	if ((tloc = time(NULL)) == TIME_MAX)
		goto err;
	if ((tmloc = (localtime(&tloc))) == NULL)
		goto err;
	if ((strftime(strdate, sizeof(strdate), "%a %b %d %T %Z %Y", tmloc))
	    == 0
	) goto err;

	if (puts(strdate) == EOF)
		goto err;

	return EXIT_SUCCESS;
err:
	perror(NULL);
	return EXIT_FAILURE;
}
