#include <stdio.h>
#include <stdlib.h>

/* 本程序用数组实现一个环形队列 */

#define INIT_QUEUE_SIZE 1024

typedef struct 
{
	int *queue;
	int head;
	int tail;
} *Queue;

int init_queue (Queue *q)
{
	if (q == NULL)
		return -1;
	*q = (Queue)malloc (sizeof(q));
	if (*q == NULL)
		return -1;
	(*q)->queue = (int*)malloc (INIT_QUEUE_SIZE*sizeof(int));
	(*q)->head = 0;
	(*q)->tail = 0;

	return 0;
}

int is_queue_empty (Queue q)
{
	if (NULL == q)
		exit (-1);
	return (q->head == q->tail);
}

int is_queue_full (Queue q)
{
	if (q == NULL)
		exit (-1);
	return ( (q->tail+1)%INIT_QUEUE_SIZE == q->head );
}

int en_queue (Queue q, int data)
{
	if (q == NULL)
		return -1;
	if (!is_queue_full (q))
	{
		q->queue[q->tail] = data;
		q->tail = (q->tail + 1)%INIT_QUEUE_SIZE;
	}
	else
	{
		printf ("error: queue full.\n");
	}
	return 0;
}


int de_queue (Queue q, int *data)
{
	if (q == NULL)
		return (-1);
	if (!is_queue_empty(q))
	{
		if (NULL != data)
			*data = q->queue[q->head];
		q->head = (q->head + 1) % INIT_QUEUE_SIZE;
	}
	else
	{
		printf ("error: queue empty.\n");
	}
	return 0;
}

int clear_queue (Queue q)
{
	if (q)
	{
		free (q->queue);
		free (q);
		q = NULL;
	}
}

int main (void)
{
	Queue q;
	init_queue (&q);
	en_queue (q, 1);
	int de_val = 0;
	de_queue (q, &de_val);
	printf ("%d\n", de_val);
	
	en_queue (q, 2);
	de_queue (q, &de_val);
	printf ("%d\n", de_val);

	clear_queue (q);
	return 0;
}


