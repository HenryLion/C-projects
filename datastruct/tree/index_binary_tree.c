#include <stdio.h>
#include <stdlib.h>


/* 本程序用来实现一下线索二叉树 */

enum tag
{
	INDEX,
	NODE,
};

// 定义线索二叉树的node节点结构
typedef struct BiTreeNode
{
	int data;
	struct BiTreeNode *l_node, *r_node;
	enum tag l_tag; // 左指针指向线索还是节点
	enum tag r_tag; // 右指针指向线索还是节点
} BiTreeNode, *BiTree;

#define STACK_SIZE 100

// 定义一个简单的栈结构用来进行二叉树节点的操作
typedef struct stack
{
	int top;
	BiTree data[STACK_SIZE];
} Stack;

Stack g_stack;

// 初始化栈
void init_stack ()
{
	g_stack.top = -1;
	int i = 0;
	for (i = 0; i < STACK_SIZE; ++i)
		g_stack.data[i] = NULL;
}

// 判断栈空
int is_empty ()
{
	return g_stack.top == -1;
}

// 判断栈满
int is_full ()
{
	return g_stack.top == (STACK_SIZE - 1);
}

// 入栈
void push (BiTreeNode *node)
{
	if (!is_full())
		g_stack.data[++g_stack.top] = node;
}

// 出栈
BiTreeNode* pop ()
{
	if (!is_empty())
		return g_stack.data[g_stack.top--];
}

/******************************************
* function:中序线索化链表的遍历算法
* date: 20200113
* author: Herbert
* comment: 线索二叉链表的中序遍历 参数T为附加的头节点指针
*  (线索二叉树左子树为线索则只想其前驱,右子树为线索则指向其后继)
*******************************************/
int mid_traverse_thread (BiTree T, void (*visit) (int data))
{
	BiTreeNode *p = T->l_node; // 附加头节点的左指针指向真正的二叉树头节点
	while ( p!= T ) // 访问结束p会指向附加的头节点
	{
		while (p->l_tag == NODE) // 找到第一个左子树为线索节点
			p = p->l_node; 
		visit (p->data); // 访问节点
		while (p->r_tag == INDEX && p->r_node != T) // 如果p的右子树是线索，表示右指针指向的就是p的后继节点则直接访问
		{
			p = p->r_node;
			visit(p->data);
		}
		p = p->r_node;
	}
	return 0;
}


/******************************************
* function: 中序建立线索链表
* date: 2020-01-13
* author: Herbert
* comment: 在中序遍历过程中修改节点的左/右指针，一保存当前访问节点的前驱和后继信息
* 遍历过程中，附设指针pre，并始终保持指针pre指向当前访问的指针p所指节点的前驱
* 严蔚敏视频21  47分钟开始
*******************************************/
void mid_thread (BiTree T)
{
	if (T)
	{
		mid_thread (T->l_node); // 左子树线索化

		if (!p->l_node)
		{
			p->l_tag = INDEX;
			p->l_node = pre;
		}
		if (!pre->r_node)
		{
			pre->r_tag = INDEX;
			pre->r_node = p;
		}

		pre = p;

		mid_thread (p->r_node); // 右子树线索化
	}
} 


