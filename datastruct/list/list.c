#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* 这个程序实现链表的交并等操作 */
#define RANDOM_LIST_LEN  ((rand()%6)+5)

#define BOOL unsigned char
#define TRUE  1
#define FALSE 0

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
void release_list (Node **head)
{
	if (NULL == head || NULL == *head)
		return;
	
	// 释放数据节点
	Node *p = (*head)->p_next;
	Node *p_n = NULL;
	while (p)
	{
		p_n = p->p_next;
		free (p);  
		p = p->p_next;
	}

	// 释放链表头
	free (*head);
	*head = NULL;
}

/****************************************************
 * function: 打印链表内容,链表内容都是int
 * author: herbert
 * date: 2019-12-06
 ****************************************************/
void debug_print_list (char *list_name, Node *head)
{
	if (NULL == head || NULL == list_name)
		return ;
	printf ("%s :",list_name);
	Node *p = head->p_next;
	while (p)
	{
		printf ("%d ", p->data);
		p = p->p_next;
	}
	printf ("\n");
}


/****************************************************
 * function: 在链表中查找某个节点是否存在
 * author: herbert
 * date: 2019-12-06
 ****************************************************/
BOOL is_node_exist (Node *head, int data)
{
	if (NULL == head)
		return FALSE;
	Node *p = head->p_next;
	while (p)
	{
		if (p->data == data)
			return TRUE;
		p = p->p_next;
	}
	return FALSE;
}

/****************************************************
 * function: 将链表B插入链表A
 * author: herbert
 * date: 2019-12-06
 ****************************************************/
Node* listSrc_insertTo_listDst (Node **head_dst, Node *head_src)
{
	if (NULL == head_dst || NULL == *head_dst)
		return NULL;
	if (NULL == head_src)
		return *head_dst;
	
	Node *new_head = *head_dst;
	Node *p = head_src->p_next;
	Node *new_node = NULL;
	while (p)
	{
		if (!is_node_exist (new_head, p->data))
		{
			new_node = (Node*)malloc (sizeof (Node));
			if (NULL != new_node)
			{
				new_node->data = p->data;
				new_node->p_next = new_head->p_next;
				new_head->p_next = new_node;
			}
			else
			{
				return new_head;
			}
		}
		p = p->p_next;
	}
	return *head_dst;
}

/****************************************************
 * function: 合并A和B链表并去重
 * author: herbert
 * date: 2019-12-06
 ****************************************************/
Node* listA_U_listB (Node *head_a, Node *head_b)
{
	if (NULL == head_a && NULL == head_b)
		return NULL;

	// 分配头节点
	Node *new_head = (Node*)malloc (sizeof(Node));
	if (NULL == new_head)
		return NULL;
	
	// 插入A链表
	listSrc_insertTo_listDst (&new_head, head_a);
	// 插入B链表
	listSrc_insertTo_listDst (&new_head, head_b);

	return new_head;

}

/****************************************************
 * function: 给链表中插入一个还不存在的节点
 * author: herbert
 * date: 2019-12-06
 ****************************************************/
void insert_node_to_list (Node *head, Node *node)
{
	if (NULL == head || NULL == node)
		return ;
	if (!is_node_exist (head, node->data))
	{
		node->p_next = head->p_next;
		head->p_next = node;
	}
	return;
}

/****************************************************
 * function: A和B链表求交集
 * author: herbert
 * date: 2019-12-07
 * comment: 返回NULL表示操作失败
 ****************************************************/
Node *listA_n_listB (Node *head_a, Node *head_b)
{
	if (NULL == head_a || NULL == head_b)
		return NULL;

	// 分配头节点
	Node *new_head = (Node*)malloc (sizeof(Node));
	if (NULL == new_head)
		return NULL;
	
	Node *p = head_a->p_next;
	Node *new_node = NULL;
	while (p)
	{
		if (is_node_exist (head_b, p->data))
		{
			new_node = (Node*)malloc (sizeof (Node));
			if (NULL == new_node)
				return NULL;
			new_node->data = p->data;
			insert_node_to_list (new_head, new_node);
		}
		p = p->p_next;
	}
	return new_head;
}


/****************************************************
 * function: 逆转单链表
 * author: herbert
 * date: 2019-12-07
 * comment: 递归方法 此函数针对没有引导头的链表
 ****************************************************/
Node *reverse_list_recursive_without_prehead (Node *head)
{
	if (NULL == head || NULL == head->p_next)
	{
		return head;
	}
	Node *new_head = NULL;
	new_head = reverse_list_recursive_without_prehead (head->p_next);
	head->p_next->p_next = head;
	head->p_next = NULL;

	return new_head;
}
/****************************************************
 * function: 逆转单链表
 * author: herbert
 * date: 2019-12-07
 * comment: 递归方法 此函数针对有引导头的链表
 ****************************************************/
Node *reverse_list_recursive (Node *head)
{
	
	if (NULL == head || NULL == head->p_next || NULL == head->p_next->p_next)
	{
		return head;
	}
	Node *new_head = head->p_next;
	head->p_next = reverse_list_recursive_without_prehead (new_head);
	return head;
}


/****************************************************
 * function: 逆转单链表
 * author: herbert
 * date: 2019-12-07
 * comment: 递推方法 (此方法没有下面的递推2简单明了)
 ****************************************************/
Node *reverse_list_recursion (Node *head)
{
	if (NULL == head || NULL == head->p_next) 
		return head;
	Node *pre = NULL;
	Node *p = head->p_next;
	Node *next = p->p_next;
	while (next)
	{
		p->p_next = pre;
		pre = p;
		p = next;
		next = next->p_next;
	}
	p->p_next = pre;
	head->p_next = p;
	return (head);
}

/****************************************************
 * function: 逆转单链表
 * author: herbert
 * date: 2019-12-07
 * comment: 递推方法 
 ****************************************************/
Node *reverse_list_recursion_ex (Node *head)
{
	if (NULL == head || NULL == head->p_next)
		return head;
	Node *pre = NULL;
	Node *p = head->p_next;
	Node *next = NULL;
	while (p)
	{
		next = p->p_next;
		p->p_next = pre;
		pre = p;
		p = next;
	}
	head->p_next = pre;
	return head;
}

int main (void)
{
	srand (time(NULL));
	Node *head = create_randLen_list();
	debug_print_list ("list1", head);

	Node *head1 = reverse_list_recursive (head);
	debug_print_list ("recursive", head1);
#if 0
	//release_list (&head);
	Node *head1 = create_randLen_list();
	debug_print_list ("list2", head1);
	//release_list (&head1);

	Node *head2 = listA_U_listB (head, head1);
	debug_print_list ("list_union",head2);
	
	Node *head3 = listA_n_listB (head, head1);
	debug_print_list ("list_n", head3);

	Node *head4 = reverse_list_recursion (head);
	debug_print_list ("recursion list1", head4);

	Node *head5 = reverse_list_recursion_ex (head1);
	debug_print_list ("recursion list2", head5);

	release_list (&head);
	release_list (&head1);
	release_list (&head2);
	release_list (&head3);
	release_list (&head4);
	release_list (&head5);
#endif
	return 0;	
}



