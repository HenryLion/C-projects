#include <stdio.h>
#include <stdlib.h>
/* 本程序实现一个队列，通过链表结构实现,不是通用队列，只能存放整数 */

typedef struct queue_node
{
	int data;
	struct queue_node *next;
} Qnode, *QNODE;

typedef struct
{
	QNODE q_head;
	QNODE q_tail;
} Queue;


typedef unsigned char BOOL;
#define TRUE  1
#define FALSE 0


int init_queue (Queue **queue)
{
	if (NULL == queue)
		return -1;
	*queue = (Queue*)malloc (sizeof(Queue));
	if (NULL == *queue)
		return -1;
	(*queue)->q_head = NULL;
	(*queue)->q_tail = NULL;
}

BOOL is_queue_empty (Queue *queue)
{
	return (NULL == queue->q_head && NULL == queue->q_tail);
}

int en_queue (Queue *queue, int data)
{
	QNODE new_node = (QNODE)malloc(sizeof(Qnode));
	if (NULL == new_node)
		return -1;
	
	new_node->data = data;
	new_node->next = NULL;
	if (is_queue_empty(queue))
	{
		queue->q_head = new_node;
		queue->q_tail = new_node;
	}
	else
	{
		queue->q_tail->next = new_node;
		queue->q_tail = new_node;
	}
	return 0;
}

int de_queue (Queue *queue, int *data)
{
	if (NULL == queue)
		return -1;
	QNODE p = NULL;
	if (!is_queue_empty (queue))
	{
		p = queue->q_head;
		if (queue->q_head == queue->q_tail)
		{
			queue->q_head = NULL;
			queue->q_tail = NULL;
		}
		else
		{
			queue->q_head = queue->q_head->next;
		}

		if (NULL != data)
		{
			*data = p->data;
		}
		free (p);
		p = NULL;
	}
	else
	{
		printf ("error: queue empty\n");
		return -1;
	}
	return 0;
}

int clear_queue (Queue *queue)
{
	if (NULL == queue)
		return 0;
	while (!is_queue_empty(queue))
	{
		de_queue (queue, NULL);
	}

	free (queue);
	queue = NULL;
}

int main (void)
{
	int idx;
	Queue *queue = NULL;
	init_queue (&queue);
	en_queue (queue, 1);
	en_queue (queue, 2);
	en_queue (queue, 3);

	int de_val = 0;
	de_queue (queue, &de_val);
	printf ("%d ", de_val);

	de_queue (queue, &de_val);
	printf ("%d ", de_val);
	
	de_queue (queue, &de_val);
	printf ("%d ", de_val);

	en_queue(queue, 4);

	de_queue (queue, &de_val);
	printf ("%d\n", de_val);
	
	for (idx = 0; idx < 10000000; ++idx)
	{
		en_queue (queue, idx);
	}

	while (!is_queue_empty(queue))
	{
		de_queue (queue, &de_val);
		printf ("%d ",de_val);
	}
	printf ("\n");
	
	clear_queue (queue);
	return 0;
}
