#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define FNAME ("/tmp/TELL_WAIT.XXXXXX")
#define LOCK 1
#define UNLOCK 0

static int fd;

static int fcntllck(int fd, int act);

int
TELL_WAIT()
{
	if (fd <= 0)
		if ((fd = (mkstemp(FNAME)) ) == -1)
			return (-1);
	return (0);
}

void
TELL_PARENT()
{
	assert(fd > 0);
	fcntllck(fd, UNLOCK);
}

void
TELL_CHILD()
{
	assert(fd > 0);
	fcntllck(fd, UNLOCK);
}

void
WAIT_PARENT()
{
	assert(fd > 0);
	fcntllck(fd, LOCK);
}

void
WAIT_CHILD()
{
	assert(fd > 0);
	fcntllck(fd, LOCK);
}

/* fcntllck: lock or unlock a fd
 *
 * lock if act is true, unlock if it is false.
 */
static int
fcntllck(int fd, int act)
{
	struct flock lock = {
		0,
		0,
		getpid(),
		act ? F_WRLCK : F_UNLCK,
		SEEK_SET
	};
	return (fcntl(fd, F_SETLKW, lock));
}
