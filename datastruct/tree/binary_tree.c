#include <stdio.h>
#include <stdlib.h>

typedef struct BiTreeNode
{
	int data;
	struct BiTreeNode *l_node, *r_node;
	// struct BiTreeNode *parent; // 加上此域表示三叉链表
} BiTreeNode, *BiTree;

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

int main (void)
{
	BiTree tree = NULL;
	tree = create_binary_tree_by_pre (&tree);
	pre_traverse_binary_tree (tree);
	return 0;
}
