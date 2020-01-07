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




