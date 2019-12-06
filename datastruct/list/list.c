#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* 这个程序实现链表的交并等操作 */
#define RANDOM_LIST_LEN  ((rand()%6)+10)

typedef struct node
{
	int data;
	struct node *p_next;
} Node;

/****************************************************
 * function: 根据一个生成的随机数生成此数据长度的链表
 * author: herbert
 * date: 2019-12-06
 ****************************************************/
Node* create_randLen_list ()
{
	int list_len = RANDOM_LIST_LEN;
	int i;
	Node *head = NULL;
	Node *new_node = NULL;
	head = (Node*)malloc (sizeof(Node));
	if (NULL == head)
		return NULL;
	head->p_next = NULL;
	
	for (i = 0; i < list_len; ++i)
	{
		new_node = (Node*)malloc (sizeof(Node));
		if (NULL == new_node)
			return head;
		scanf ("%d",&(new_node->data));

		new_node->p_next = head->p_next;
		head->p_next = new_node;
	}

	return head;
}
/****************************************************
 * function: 释放链表
 * author: herbert
 * date: 2019-12-06
 ****************************************************/
void release_list (Node *head)
{
	if (NULL == head)
		return;
	
	// 释放数据节点
	Node *p = head->p_next;
	Node *p_n = NULL;
	while (p)
	{
		p_n = p->p_next;
		free (p);  
		p = p->p_next;
	}

	// 释放链表头
	free (head);
	head = NULL;

}

/****************************************************
 * function: 打印链表内容,链表内容都是int
 * author: herbert
 * date: 2019-12-06
 ****************************************************/
void debug_print_list (Node *head)
{
	if (NULL == head)
		return ;
	Node *p = head->p_next;
	while (p)
	{
		printf ("%d ", p->data);
		p = p->p_next;
	}
	printf ("\n");
}

int main (void)
{
	srand (time(NULL));
	Node *head = create_randLen_list();
	debug_print_list (head);
	release_list (head);
	return 0;	
}



