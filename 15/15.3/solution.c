#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	FILE *fp;
	char buf[BUFSIZ];
	size_t n;

	if ((fp = popen("fuck", "r")) == NULL)
		goto err;

	fprintf(stderr, "popen succeeded\n");
	while ((n = fread(&buf, 1, sizeof(buf), fp)) != 0) {
		while ((n -= fwrite(&buf, 1, n, stdout)) > 0)
			;
	} if (feof(fp)) {
	} else if (ferror(fp)) {
		goto err;
	} else {
		goto err;
	}

	return (EXIT_SUCCESS);
err:
	perror(NULL);
	fprintf(stderr, "failed to popen invalid command\n");
}
