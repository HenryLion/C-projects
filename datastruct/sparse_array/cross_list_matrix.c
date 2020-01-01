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
	if (node->r_idx >= MAX_ROW || node->c_idx >= MAX_COL)
	{
		printf ("insert position error!\n");
		return -1;
	}
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
	{
		p_col->col_next = node;
		matrix->node_num++;
		printf ("col %d first node insert. \n", col);
	}
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
				matrix->node_num++;
				printf ("col %d middle insert.\n", col);
				break;
			}
		}
		if (!p_col)
		{
			pre->col_next = node;
			matrix->node_num++;
			printf ("col %d tail insert.\n", col);
		}
	}

	return 0;
}

/***************************************
* function: 从一个十字链表中删除一个节点(如果存在的话)
* author: Herbert
* date: 2020-01-01
* param: row,col 删除节点的行列坐标
* comment:
***************************************/
int delete_node (Matrix *matrix, int row, int col)
{
	if (NULL == matrix)
		return 0;

	if (row  >= MAX_ROW || col >= MAX_COL)
	{
		printf ("delete position error!\n");
		return -1;
	}

	// 节点不存在直接返回
	if (!is_node_exist(matrix, row, col))
	{
		printf ("delete node not exist\n");
		return 0;
	}
	
	// 先删除行指针,只改变指针不释放节点
	matrix_node_t *p_row = matrix->row_head[row];
	matrix_node_t *pre = p_row;
	if (p_row->row_next == NULL)
	{
		//never here,节点不存在的情况在前面已经判断过了
		return 0;
	}
	else
	{
		p_row = p_row->row_next;
		while (p_row)
		{
			if (p_row->c_idx == col)
			{
				pre->row_next = p_row->row_next;
				break;
			}
			else
			{
				pre = p_row;
				p_row = p_row->row_next;
			}
		}
		if (!p_row) // never here 此种情况还是没有找到节点
			return 0;
	}

	// 再删除列指针,释放节点空间
	matrix_node_t *p_col = matrix->col_head[col];
	pre = p_col;
	if (p_col->col_next == NULL)
	{
		// never here
		return 0;
	}
	else
	{
		p_col = p_col->col_next;
		while (p_col)
		{
			if (p_col->r_idx == row)
			{
				pre->col_next = p_col->col_next;
				free (p_col);
				matrix->node_num--;
				return 0;
			}
			else
			{
				pre = p_col;
				p_col = p_col->col_next;
			}
		}
		if (!p_col)
			return 0;
	}
	return 0;
}

/***************************************
* function: 以行序打印一个十字链表
* author: Herbert
* date: 2020-01-01
* comment:
***************************************/
void print_linked_matrix_by_row (Matrix *matrix)
{
	if (NULL == matrix)
		return;
	int i = 0;
	matrix_node_t *p_node = NULL;
	printf ("matrix node_num = %d, nodes by row is:\n", matrix->node_num);
	for (i = 0; i < MAX_ROW; ++i)
	{
		p_node = matrix->row_head[i]->row_next;
		while (p_node)
		{
			printf ("(%d,%d)=%d ", p_node->r_idx, p_node->c_idx, p_node->value);
			p_node = p_node->row_next;
		}
	}
	printf ("\n");
	return;
}

/***************************************
* function: 以列序打印一个十字链表
* author: Herbert
* date: 2020-01-01
* comment:
***************************************/
void print_linked_matrix_by_col (Matrix *matrix)
{
	if (NULL == matrix)
		return;
	int i = 0;
	matrix_node_t *p_node = NULL;
	printf ("matrix node_num = %d, nodes by col is:\n", matrix->node_num);
	for (i = 0; i < MAX_COL; ++i)
	{
		p_node = matrix->col_head[i]->col_next;
		while (p_node)
		{
			printf ("(%d,%d)=%d ", p_node->r_idx, p_node->c_idx, p_node->value);
			p_node = p_node->col_next;
		}
	}
	printf ("\n");
	return;
}

int main (void)
{
	Matrix *matrix = create_empty_matrix ();
	int row, col, value;
	matrix_node_t *node = NULL;
	while (1)
	{
		printf ("Input: ");
		scanf ("%d %d %d", &row, &col, &value);
		if (row >= MAX_ROW || col >= MAX_COL)
			break;
		node = create_node (row,col,value);
		insert_node (matrix, node);
	}
	print_linked_matrix_by_row (matrix);
	print_linked_matrix_by_col (matrix);

	while (1)
	{
		printf ("delete: ");
		scanf ("%d %d", &row, &col);
		if (row >= MAX_ROW || col >= MAX_COL)
			break;
		delete_node (matrix, row, col);
	}

	print_linked_matrix_by_row (matrix);
	print_linked_matrix_by_col (matrix);

	return 0;
}
