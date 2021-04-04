#include <stdlib.h>
#include <pthread.h>

struct job {
	struct job *j_next;
	struct job *j_prev;
	pthread_t   j_id;   /* tells which thread handles this job */
	/* ... more stuff here ... */
};

struct queue {
	struct job      *q_head;
	struct job      *q_tail;
	pthread_mutex_t q_lock; /* queue is being read/written */
	pthread_cond_t  q_cond; /* unblock when there is more in the queue */
};

/*
 * Initialize a queue.
 */
int
queue_init(struct queue *qp)
{
	qp->q_head = NULL;
	qp->q_tail = NULL;
	qp->q_lock = PTHREAD_MUTEX_INITIALIZER;
	qp->q_cond = PTHREAD_COND_INITIALIZER;
	/* ... continue initialization ... */
	return(0);
}

/*
 * Insert a job at the head of the queue.
 */
void
job_insert(struct queue *qp, struct job *jp)
{
	pthread_mutex_lock(&qp->q_lock);
	jp->j_next = qp->q_head;
	jp->j_prev = NULL;
	if (qp->q_head != NULL)
		qp->q_head->j_prev = jp;
	else
		qp->q_tail = jp;	/* list was empty */
	qp->q_head = jp;
	pthread_mutex_unlock(&qp->q_lock);
	pthread_cond_signal(&qp->q_cond);
}

/*
 * Append a job on the tail of the queue.
 */
void
job_append(struct queue *qp, struct job *jp)
{
	pthread_mutex_lock(&qp->q_lock);
	jp->j_next = NULL;
	jp->j_prev = qp->q_tail;
	if (qp->q_tail != NULL)
		qp->q_tail->j_next = jp;
	else
		qp->q_head = jp;	/* list was empty */
	qp->q_tail = jp;
	pthread_mutex_unlock(&qp->q_lock);
	pthread_cond_signal(&qp->q_cond);
}

/*
 * Remove the given job from a queue.
 */
void
job_remove(struct queue *qp, struct job *jp)
{
	pthread_mutex_lock(&qp->q_lock);
	if (jp == qp->q_head) {
		qp->q_head = jp->j_next;
		if (qp->q_tail == jp)
			qp->q_tail = NULL;
		else
			jp->j_next->j_prev = jp->j_prev;
	} else if (jp == qp->q_tail) {
		qp->q_tail = jp->j_prev;
		jp->j_prev->j_next = jp->j_next;
	} else {
		jp->j_prev->j_next = jp->j_next;
		jp->j_next->j_prev = jp->j_prev;
	}
	pthread_mutex_unlock(&qp->q_lock);
}

/*
 * Find a job for the given thread ID.
 */
struct job *
job_find(struct queue *qp, pthread_t id)
{
	struct job *jp;

	if (pthread_mutex_lock(&qp->q_lock) != 0)
		return(NULL);

	for (jp = qp->q_head; ; jp = jp->j_next) {
		if (pthread_equal(jp->j_id, id))
			break;

		if (jp == NULL) {
			pthread_cond_wait(&qp->q_cond, &qp->q_lock);
			pthread_mutex_unlock(&qp->q_lock);
			return job_find(qp, id);
		}
	}


	pthread_mutex_unlock(&qp->q_lock);
	return(jp);
}
