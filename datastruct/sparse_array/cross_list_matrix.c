#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cross_list_matrix.h"
/* 本程序用十字链表来表示矩阵 */

/***************************************
* function: 创建一个节点
* author: Herbert
* date: 2019-12-30
* comment: 根据输入值新建一个node节点
***************************************/
matrix_node_t* create_node (int row, int col, int val)
{
	matrix_node_t *p_node = (matrix_node_t*)malloc (sizeof (matrix_node_t));
	if (NULL == p_node)
		return NULL;
	p_node->r_idx = row;
	p_node->c_idx = col;
	p_node->value = val;
	p_node->row_next = NULL;
	p_node->col_next = NULL;
	return p_node;
}

/***************************************
* function: 初始化一个矩阵
* author: Herbert
* date: 2019-12-30
* comment: 生成一个空的十字链表表示的矩阵并返回它
***************************************/
Matrix *create_empty_matrix ()
{
	Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
	if (NULL == matrix)
		return NULL;
	memset (matrix, 0, sizeof (Matrix));

	// 初始化row_head和col_head数组
	int i = 0;
	for (i = 0; i < MAX_ROW; ++i)
	{
		matrix->row_head[i] = create_node (-1, -1, INVALID_DATA);
		if (matrix->row_head[i] == NULL)
			return NULL;
	}
	for (i = 0; i < MAX_COL; ++i)
	{
		matrix->col_head[i] = create_node (-1, -1, INVALID_DATA);
		if (matrix->col_head[i] == NULL)
			return NULL;
	}
	return matrix;
}
	
/***************************************
* function: 判断一个节点是否已经存在
* author: Herbert
* date: 2019-12-30
* comment: 在插入一个新的节点时需要判断它是否已经存在
***************************************/
BOOL is_node_exist (Matrix *matrix, int row, int col)
{
	if (NULL == matrix || 0 == matrix->node_num)
		return FALSE;
	matrix_node_t *p = matrix->row_head[row];
	while (p)
	{
		if (p->row_next->c_idx == col)
			return TRUE;
		p = p->row_next;
	}
	return FALSE;
}


/***************************************
* function: 将一个节点插入十字矩阵
* author: Herbert
* date: 2019-12-30
* comment:
***************************************/
int insert_node (Matrix *matrix, matrix_node_t *node)
{
	if (NULL == matrix || NULL == node)
		return -1;
	char input;
	int row = node->r_idx;
	int col = node->c_idx;

	// 先插入到行的合适位置
	matrix_node_t *p_row = matrix->row_head[row];
	matrix_node_t *pre = matrix->row_head[row];
	if (NULL == p_row->row_next)
		p_row->row_next = node;
	else
	{
		p_row = p_row->row_next;
		while (p_row)
		{
			if (p_row->c_idx < node->c_idx)
			{
				pre = p_row;
				p_row = p_row->row_next;
			}
			else if (p_row->c_idx == node->c_idx)
			{
				printf ("node (%d,%d) is exist, do you want to modify it? ", node->r_idx, node->c_idx);
				scanf ("%c", &input);
				if ('y' == input)
					p_row->value = node->value;
				else if ('n' == input)
					;
				return 0;
			}
			else
			{
				node->row_next = p_row;
				pre->row_next = node;
				break;
			}
		}

		if (!p_row)
		{
			pre->row_next = node;
		}
	}

	// 再插入到列的合适位置
	matrix_node_t *p_col = matrix->col_head[col];
	pre = matrix->col_head[col];
	if (NULL == p_col->col_next)
		p_col->col_next = node;
	else
	{
		p_col = p_col->col_next;
		while (p_col)
		{
			if (p_col->r_idx < node->r_idx)
			{
				pre = p_col;
				p_col = p_col->col_next;
			}
			else if (p_col->r_idx == node->r_idx)
			{
				// never here! do nothing, the same position element has been processed when deal with p_row before;
				return 0;
			}
			else
			{
				node->col_next = p_col;
				pre->col_next = node;
				break;
			}
		}
		if (!p_col)
			pre->col_next = node;
	}

	return 0;
}

int main (void)
{
	Matrix *matrix = create_empty_matrix ();
	matrix_node_t *node = create_node (2,3,5);
	insert_node (matrix, node);
	return 0;
}
