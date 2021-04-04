#define _POSIX_C_SOURCE 200909L

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>

int pstatmemb(const struct stat *);

int
main(void)
{
	int sockfd;
	struct stat sp;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		goto err;
	if (fstat(sockfd, &sp) == -1)
		goto err;
	if (pstatmemb(&sp) == -1)
		goto err;

	return (EXIT_SUCCESS);
err:
	perror(NULL);
	return (EXIT_FAILURE);
}

int
pstatmemb(const struct stat *sp)
{
	int ret;
	/* The underlying types for struct stat's members and struct
	 * timespec' members are from POSIX sys/stat.h.
	 * "integer types" are cast to long.
	 * "signed integer" types are cast to long.
	 * "unsigned integer" types are cast to unsigned long.
	 */

	if ((ret = printf("START OF POSIX OPTIONS:\n")) < 0)
		goto err;

	if ((ret = printf("st_dev = %ld\n", (long)sp->st_dev)) < 0)
		goto err;
	if ((ret = printf("st_ino = %lu\n", (unsigned long)sp->st_ino)) < 0)
		goto err;
	if ((ret = printf("st_mode = %ld\n", (long)sp->st_mode)) < 0)
		goto err;
	if ((ret = printf("st_nlink = %ld\n", (long)sp->st_nlink)) < 0)
		goto err;
	if ((ret = printf("st_uid = %ld\n", (long)sp->st_uid)) < 0)
		goto err;
	if ((ret = printf("st_gid = %ld\n", (long)sp->st_gid)) < 0)
		goto err;
	if ((ret = printf("st_rdev = %ld\n", (long)sp->st_rdev)) < 0)
		goto err;
	if ((ret = printf("st_size = %ld\n", (long)sp->st_size)) < 0)
		goto err;
	if ((ret = printf("st_atim.tv_sec = %ld\n", (long)sp->st_atim.tv_sec))
	    < 0)
		goto err;
	if ((ret = printf("st_atim.tv_nsec = %ld\n", sp->st_atim.tv_nsec))
	    < 0)
		goto err;
	if ((ret = printf("st_mtim.tv_sec = %ld\n", (long)sp->st_mtim.tv_sec))
	    < 0)
		goto err;
	if ((ret = printf("st_mtim.tv_nsec = %ld\n", sp->st_mtim.tv_nsec))
	    < 0)
		goto err;
	if ((ret = printf("st_ctim.tv_sec = %ld\n", (long)sp->st_ctim.tv_sec))
	    < 0)
		goto err;
	if ((ret = printf("st_ctim.tv_nsec = %ld\n", sp->st_ctim.tv_nsec))
	    < 0)
		goto err;
	if ((ret = printf("st_blksize = %ld\n", (long)sp->st_blksize)) < 0)
		goto err;
	if ((ret = printf("st_blocks = %ld\n", (long)sp->st_blocks)) < 0)
		goto err;

#if defined(__OpenBSD__)
	if ((ret = printf("\nSTART OF OpenBSD OPTIONS:\n")) < 0)
		goto err;
	if ((ret = printf("st_flags = %lu\n", (unsigned long)sp->st_flags))
	    < 0)
		goto err;
	if ((ret = printf("st_gen = %lu\n", (unsigned long)sp->st_gen)) < 0)
		goto err;
#endif /* defined(__OpenBSD__) */

	return (0);
err:
	return (ret);
}
