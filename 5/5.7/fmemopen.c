/* Copyright (c) 2020 Anonymous
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* fmemopen for platforms with a funopen function, chiefly OpenBSD.
 * Written as a solution for exercise 5.11 from APUE.
 */

/* #define _POSIX_C_SOURCE 200809L */
/* #define __BSD_VISIBLE */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fmemopen.h"

struct flags {
	/* mode flags */
	unsigned int r :1;
	unsigned int w :1;
	unsigned int a :1;
	unsigned int p :1; /* p for plus, the + flag */
	unsigned int b :1; /* unused and ignored */
	unsigned int err :1; /* error in mode string */

	/* special flags */
	unsigned int alloc :1; /* buffer was alocated by us */
};

struct memfile {
	unsigned char *buffer; /* the memory buffer */
	size_t size; /* the size of the memory buffer */
	size_t len; /* the length of the data within it */
	fpos_t pos; /* the byte position we're at */
	struct flags flags; /* various flags */
};

static struct flags convmode(const char *);
static struct memfile *malloc_memfile(void *, size_t, struct flags);
static void initmemfilepos(struct memfile *const);
static int readfn(void *, char *, int);
static int writefn(void *, const char *, int);
static fpos_t seekfn(void *, fpos_t, int);
static int closefn(void *);
static int writable(struct flags);

extern FILE *
fmemopen(void *buffer, size_t size, const char *mode)
{
	void *cookie;
	struct flags flags = convmode(mode);
	FILE *retfile;

	if ((cookie = malloc_memfile(buffer, size, flags)) == NULL)
		return (NULL);

	if (
	    (retfile = funopen(cookie, &readfn, &writefn, &seekfn, &closefn))
	    == NULL
	) return (NULL);

	return (retfile);
}

/* convmode: populates a struct flags with a fopen mode string
 *
 * flags.err is set on error.
 */
static struct flags
convmode(const char *mode)
{
	struct flags flags = {0};

	for (; *mode && flags.err == 0; mode++)
		switch (*mode) {
		case 'r':
			flags.r = 1;
			if (flags.w || flags.a)
				flags.err = 1;
			break;
		case 'w':
			flags.w = 1;
			if (flags.r || flags.a)
				flags.err = 1;
			break;
		case 'a':
			flags.a = 1;
			if (flags.r || flags.w)
				flags.err = 1;
			break;
		case 'b':
			flags.b = 1;
			break;
		case '+':
			flags.p = 1;
			break;
		default:
			flags.err = 1;
			goto end;
		}

	if (flags.r == 0 && flags.w == 0 && flags.a == 0)
		flags.err = 1;
end:
	return (flags);
}

static struct memfile *
malloc_memfile(void *buffer, size_t size, struct flags flags)
{
	struct memfile *memfile;
	if ((memfile = malloc(sizeof(struct memfile))) == NULL)
		goto err;
	if (size == 0 || flags.err)
		goto errerrno;
	if (buffer == NULL) {
		if (flags.p == 0)
			goto errerrno;
		if ((buffer = malloc(size)) == NULL)
			goto err;
		flags.alloc = 1;
	}

	memfile->buffer = buffer;
	memfile->size = size;
	memfile->flags = flags;
	memfile->len = size;
	initmemfilepos(memfile);

	return (memfile);
errerrno: /* For when we fail and must set errno. */
	errno = EINVAL;
err: /* For when we fail and errno is set for us. */
	if (flags.alloc)
		free(buffer);
	free(memfile);
	return (NULL);
}

/* initmemfilepos: set the proper starting position for memfile */
static void
initmemfilepos(struct memfile *const cookie)
{
	size_t i;
	if (cookie->flags.alloc || cookie->flags.r || cookie->flags.w) {
		cookie->pos = 0;
		return;
	}

	/* all other modes excluded, we're on append mode */
	for (i = 0; cookie->buffer[i] && i <= cookie->size; i++)
		;
	cookie->pos = i;
}

static int
readfn(void *cookie, char *buf, int nbytes)
{
	struct memfile *memfile = cookie;
	int len;
	if (nbytes < 0 || (memfile->flags.r == 0 && memfile->flags.p == 0))
		goto err;
	len = memfile->size - memfile->pos < (unsigned int)nbytes ?
	    memfile->size - memfile->pos : nbytes;

	memcpy(buf, &memfile->buffer[memfile->pos], len);
	memfile->pos += len;

	return (len);
err:
	errno = EINVAL;
	return (-1);
}

static int
writefn(void *cookie, const char *buf, int nbytes)
{
	struct memfile *memfile = cookie;
	int len;
	if (nbytes < 0 || !writable(memfile->flags))
		goto err;
	len = memfile->size - memfile->pos < (unsigned int)nbytes ?
	    memfile->size - memfile->pos : nbytes;

	if (memfile->flags.a)
		memfile->pos = memfile->len;
	memcpy(&memfile->buffer[memfile->pos], buf, len);
	memfile->pos += len;
	memfile->len += len;
	if (memfile->flags.a)
		memfile->buffer[memfile->len] = '\0';

	return (len);
err:
	errno = EINVAL;
	return (-1);
}

static fpos_t
seekfn(void *cookie, fpos_t offset, int whence)
{
	fpos_t rval = -1;
	struct memfile *memfile = cookie;

	switch (whence) {
	case SEEK_SET:
		rval = memfile->pos = offset;
		break;
	case SEEK_CUR:
		rval = memfile->pos += offset;
		break;
	case SEEK_END:
		rval = memfile->pos = memfile->len - offset;
		break;
	default:
		errno = EINVAL;
		break;
	}

	return (rval);
}

static int
closefn(void *cookie)
{
	struct memfile *memfile = cookie;
	if (memfile->flags.alloc)
		free(memfile->buffer);
	else if (writable(memfile->flags))
		memfile->buffer[memfile->len] = 0;
	free(memfile);
	return (0);
}

/* writable: return true if the struct flags says "open for writing"
 *
 * That means any kind of write. Append, update, or write.
 */
static int
writable(struct flags flags)
{
	return (flags.w || flags.a || flags.p);
}
