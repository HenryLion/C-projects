#include <stdio.h>
#include <stdlib.h>

typedef struct BiTreeNode
{
	int data;
	struct BiTreeNode *l_node, *r_node;
	// struct BiTreeNode *parent; // 加上此域表示三叉链表
} BiTreeNode, *BiTree;

#define STACK_SIZE 100

// 定义一个简单的栈结构用来进行非递归中序遍历二叉树
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



/****************************************************
* function: 根据一颗二叉树的先序遍历序列生成二叉树
* author: Herbert
* date: 2020-01-10
* comment: eg: 12300045000   0表示空树
****************************************************/
BiTree create_binary_tree_by_pre (BiTree *T)
{
	int ch;
	scanf ("%d", &ch);
	//scanf ("%*[^\n]%*c");
	if (ch != 0)
	{
		*T = (BiTree)malloc (sizeof(BiTreeNode));
		if (NULL == T)
			exit (1);
		(*T)->data = ch;
		(*T)->l_node = create_binary_tree_by_pre ( &(*T)->l_node );
		(*T)->r_node = create_binary_tree_by_pre ( &(*T)->r_node );
	}
	else
	{
		return NULL;
	}
	return *T;
}


/****************************************************
* function: 先序遍历二叉树
* author: Herbert
* date: 2020-01-10
* comment:  
****************************************************/
int pre_traverse_binary_tree (BiTree root)
{
	if (!root)
		return 0;
	// 访问根节点数据
	printf ("%d ", root->data);

	pre_traverse_binary_tree (root->l_node);
	pre_traverse_binary_tree (root->r_node);
	
	return 0;
}

/****************************************************
* function: 中序遍历二叉树
* author: Herbert
* date: 2020-01-11
* comment:  
****************************************************/
int inter_traverse_binary_tree (BiTree root)
{
	if (!root)
		return 0;
	inter_traverse_binary_tree (root->l_node);
	printf ("%d ", root->data);
	inter_traverse_binary_tree (root->r_node);
	return 0;
}
/****************************************************
* function: 后序遍历二叉树
* author: Herbert
* date: 2020-01-11
* comment:  
****************************************************/
int post_traverse_binary_tree (BiTree root)
{
	if (!root)
		return 0;
	post_traverse_binary_tree (root->l_node);
	post_traverse_binary_tree (root->r_node);
	printf ("%d ", root->data);

	return 0;
}

/****************************************************
* function: 由二叉树的根找到它第一个左子树为空的节点并返回此节点
* author: Herbert
* date: 2020-01-12
* comment: 一直往左走，如果其节点左子树不为空则入栈
* return: 树为空则返回空,否则返回首个左子树为空的节点
****************************************************/
BiTreeNode * go_far_left_node (BiTree T)
{
	if (NULL == T)
		return NULL;
	while (T->l_node)
	{
		push (T);
		T = T->l_node;
	}
	return T;
}

/****************************************************
* function: 非递归中序遍历二叉树
* author: Herbert
* date: 2020-01-12
* comment: 使用栈
****************************************************/
int inter_traverse_binary_tree_nonrecusive (BiTree root)
{
	BiTreeNode *node = go_far_left_node (root);
	while (node)
	{
		printf ("%d ", node->data); // 访问此节点
		if (node->r_node)
		{
			node = go_far_left_node (node->r_node);
		}
		else if (!is_empty ())
		{
			node = pop ();
		}
		else
			node = NULL;
	}
	return 0;
}


int main (void)
{
	BiTree tree = NULL;
	tree = create_binary_tree_by_pre (&tree);
	pre_traverse_binary_tree (tree);
	printf ("\n");
	inter_traverse_binary_tree (tree);
	printf ("\n");
	post_traverse_binary_tree (tree);
	printf ("\n");
	inter_traverse_binary_tree_nonrecusive (tree);
	printf ("\n");
	return 0;
}
