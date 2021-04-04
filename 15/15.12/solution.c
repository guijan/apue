#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

#define KEY_T_MAX ((key_t)-1)

int
main(void)
{
	int i;
	int msqid;
	key_t key;
	struct mymsg *msg;

	if ((key = ftok("tok.txt", 0)) == KEY_T_MAX) {
		(void)fprintf(stderr, "ftok failed\n");
		goto err;
	}
	for (i = 5; i > 0; i--) {
		if ((msqid = msgget(key, 0700 | IPC_CREAT)) == -1)
			goto err;
		if (printf("loop 1 identifier: %d\n", msqid) < 0)
			goto err;
		if (msgctl(msqid, IPC_RMID, NULL) == -1)
			goto err;
	}
	if ((msg = malloc(sizeof(struct mymsg) + 128)) == NULL)
		goto err;
	strlcpy(msg->mtext, "I really do hate niggers", 128);
	for (i = 5; i > 0; i--) {
		if ((msqid = msgget(IPC_PRIVATE, 0700 | IPC_CREAT)) == -1)
			goto err;
		if (msgsnd(msqid, msg, sizeof(struct mymsg) + 128, 0) == -1)
			goto err;
		if (printf("loop 2 identifier: %d\n", msqid) < 0)
			goto err;
/*		if (msgctl(msqid, IPC_RMID, NULL) == -1)
			goto err;
*/
	}
	return (EXIT_SUCCESS);
err:
	perror(NULL);
	return (EXIT_FAILURE);
}
