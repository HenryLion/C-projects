#include <stdio.h>

/* 本程序记录一下二叉树一些递归操作的例子 */

/* 1、统计二叉树中叶子节点的个数,伪代码 */
/* 叶子节点的个数=左子树叶子节点个数+右子树叶子节点个数 */
// 自己写的求叶子节点个数
int get_binarytree_leaf (BiTree *root, int *num)
{
	if (NULL == root)
		return 0;
	
	if (NULL == root->l_node && NULL == root->r_node)
		*num++;
	
	get_binarytree_leaf (root->l_node,num);
	get_binarytree_leaf (root->r_node,num);

	return 0;
}

// 严蔚敏(ywm)视频中代码求叶子节点个数
void ywm_get_binarytree_leaf (BiTree *T, int *num)
{
	if (T) // 树不为空
	{
		if (NULL == T->l_node && NULL == T->r_node) // 如果是叶子节点
			*num++;
		// 其实可以将下面两句写入到else分支里面
		ywm_get_binarytree_leaf (T->l_node, num);
		ywm_get_binarytree_leaf (T->r_node, num);
	}
}


/* 2、求二叉树的深度 */
/* 二叉树深度=1+max(左子树深度,右子树深度) */

// 自己写的求二叉树的深度
int get_depth (BiTree *T)
{
	int l_depth = 0;
	int r_depth = 0;
	if (NULL == T)
		return 0;
	l_depth = get_depth (T->l_node);
	r_depth = get_depth (T->r_node);
	return 1 + (l_depth > r_depth ? l_depth : r_depth);
}

// ywm视频中代码求二叉树深度,和我自己写的逻辑是一样的
int ywm_get_depth (BiTree *T)
{
	if (NULL == T)
		depthval = 0;
	else
	{
		depthLeft = ywm_get_depth (T->l_node);
		depthRight = ywm_get_depth (T->r_node);
		depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
	}
	return depthval;
}

/* 3、复制二叉树 */
/* 建立根节点 复制左子树 复制右子树 根节点左指针指向左子树 右指针指向右子树 */

// 我的复制二叉树实现,我这种实现方式从代码量上来看比下面严蔚敏那种方式还简单一些.
BiTree * copy_binary_tree (BiTree *T)
{
	if (NULL == T)
		return NULL;
	BiTree *new_node = (BiTree *)malloc (sizeof (BiTree));
	if (NULL == new_node)
		return NULL;
	
	new_node->data = T->data;
	new_node->l_node = copy_binary_tree (T->l_node);
	new_node->r_node = copy_binary_tree (T->r_node);

	return new_node;
}

// ywm实现复制二叉树方式
BiTree *GetTreeNode (int data, BiTree *lptr, BiTree *rptr)
{
	if (!(T = (BiTree*)malloc (sizeof (BiTree))))
		exit (1);
	T->data = data;
	T->l_node = lptr;
	T->r_node = rptr;

	return T;
}

BiTree *ywm_copy_binary_tree (BiTree *T)
{
	if (!T)
		return NULL;
	if (T->l_node)
		lptr = ywm_copy_binary_tree (T->l_node);
	else 
		lptr = NULL;
	
	if (T->r_node)
		rptr = ywm_copy_binary_tree (T->r_node);
	else
		rptr = NULL;
	
	newnode = GetTreeNode (T->data, lptr, rptr);
	return newnode;
}

/* 4、按照给定的先序序列建立二叉链表,伪代码 eg:"ABC---DE---"可以创建一棵二叉树 */
int create_binary_tree (BiTree **T) // T是一个out型参数
{
	scanf (&ch);
	if (ch == '-') 
		*T = NULL;
	else
	{
		if (!(*T = (BiTree*)malloc (sizeof (BiTree))))
			exit (1);
		*T->data = ch; // 生成根节点并赋值
		create_binary_tree (&T->l_node); //生成左子树 
		create_binary_tree (&T->r_node); //生成右子树
	}
	return 0;
}

/* 5、 按给定的表达式前序序列建相应二叉树(a+b)*c-d/e ->前序: -x+abc/de */
int create_binary_tree_by_pre (BiTree **T)
{
	scanf (&ch)
	if (ch == num) // ch是操作数
	{
		*T = malloc (sizeof(BiTree));
		*T->data = num;
		*T->l_node = NULL;
		*T->r_node = NULL;
	}
	else // ch是操作符
	{
		*T = malloc (sizeof (BiTree));
		*T->data = ch;
		create_binary_tree_by_pre (*T->l_node);
		create_binary_tree_by_pre (*T->r_node);
	}
	return 0;
} 

/* 6、按给定的表达式后缀序列建相应二叉树(a+b)*c-d/e ->后缀: ab+c*de/- */

// 递归法感觉不能解决这个问题，需要用栈
int create_binary_tree_by_post (BiTree **T)
{
	scanf (&ch)
	if (ch = num) // ch是操作数
	{
		*lptr = malloc (sizeof(BiTree));
		*T
	}
	else //ch是操作符
	{
		
	}
	return 0;
}



