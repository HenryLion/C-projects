#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sparse_array.h"

/**********************************************
* function: 生成一个稀疏矩阵
* author: Herbert
* date: 2019-12-26
**********************************************/
Sparse_matrix* create_sparse_matrix (Sparse_matrix **s_matrix)
{
	if (NULL == s_matrix)
		return NULL;
	*s_matrix = (Sparse_matrix*)malloc (sizeof (Sparse_matrix));
	if (*s_matrix == NULL)
		return NULL;

	memset (*s_matrix, 0, sizeof (Sparse_matrix));
	return *s_matrix;
}


/**********************************************
* function: 判断一个行列坐标元素在矩阵中是否已经存在,如果存在则将其value带出
* author: Herbert
* date: 2019-12-26
**********************************************/
int is_matrix_node_exist (Sparse_matrix *s_matrix, int r_idx, int c_idx, int *val)
{
	if (NULL == s_matrix)
		return 0;
	int i;
	for (i = 0; i < s_matrix->node_num; ++i)
	{
		if ( (s_matrix->nodes[i].r_idx == r_idx) && (s_matrix->nodes[i].c_idx == c_idx) )
		{
			if (NULL != val)
				*val = s_matrix->nodes[i].value;
			return 1;
		}
	}
	return 0;
}

/**********************************************
* function: 打印一个稀疏矩阵
* author: Herbert
* date: 2019-12-25
**********************************************/
void print_sparse_matrix (Sparse_matrix *s_matrix)
{
	if (NULL == s_matrix)
		return;
	int i;
	printf ("\nmatrix row = %d, col = %d, node_num = %d:\n", s_matrix->row, s_matrix->col, s_matrix->node_num);
	for (i = 0; i < s_matrix->node_num; ++i)
	{
		printf ("(%d,%d) = %-2d  ", s_matrix->nodes[i].r_idx, s_matrix->nodes[i].c_idx,s_matrix->nodes[i].value); 
		if ( (i+1) % 6 == 0)
			printf ("\n");
	}
	printf ("\nrow_first_idx :\n");
	for (i = 0; i < s_matrix->row+1; ++i)
		printf ("%d ", s_matrix->row_first[i]);
	printf ("\n");
	return;
}

/**********************************************
* function: 实现一个普通的矩阵转置运算
* author: Herbert
* date: 2019-12-25
**********************************************/
int* matrix_transpose (int *matrix, int row, int col)
{
	int i,j;
	int *p = (int*)malloc (row * col * sizeof(int));
	if (NULL == p)
		return NULL;
	
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			p[j*row+i]  = matrix[i*col+j];
		}
	}

	return p;
}

/**********************************************
* function: 打印二维数组 用一维数组的形式表示二维数组，其实这也是二维数组的真实表示法
* author: Herbert
* date: 2019-12-25
**********************************************/
void print_two_dimensional_array (int *arr, int row, int col)
{
	int i;
	for (i = 0; i < row * col; ++i)
	{
		printf ("%2d ", arr[i]);
		if ((i+1) % col == 0)
			printf ("\n");
	}
	return ;
}

/**********************************************
* function: 初始化一个普通的二维数组(矩阵)
* author: Herbert
* date: 2019-12-26
**********************************************/
void init_two_dimensional_array (int *arr)
{
	if (NULL == arr)
		return ;
	int non_zero_num = (ROW*COL) / 20 + 5; 
	int i;
	for (i = 0; i < non_zero_num; ++i)
	{
		arr[rand()%(ROW*COL)] = rand () % 100;
	}
	return ;
}

/**********************************************
* function: 从普通的二维数据表示得到稀疏矩阵的表示
* author: Herbert
* date: 2019-12-26 将每行首元素在nodes中的索引存放在row_first中,
*   为了得到最后一行非零元素的个数,需要row_first比实际行数多一项，以便用来计算最后一行非零元素个数
**********************************************/
void get_sparse_matrix_from_normal_matrix (int *arr, int row, int col, Sparse_matrix *s_matrix)
{
	if (NULL == arr || NULL == s_matrix)
		return;
	int i;
	int j;
	s_matrix->row = row;
	s_matrix->col = col;
	int node_num = 0;
	int last_row_num = -1;

	// 初始化行首元素在s_matrix->nodes中的索引为-1
	for (i = 0; i <= row; ++i)
		s_matrix->row_first[i] = -1;

	for (i = 0; i < row * col; ++i)
	{
		if (arr[i] != 0)
		{
			s_matrix->nodes[node_num].r_idx = i / col;
			s_matrix->nodes[node_num].c_idx = i % col;
			s_matrix->nodes[node_num].value = arr[i];
			if (i / col != last_row_num)
			{
				// 行号发生变化时可能中间有全0行，需要将全0行的row_first值设置为node_num
				if (i / col - (last_row_num+1) > 0) // 说明在i/col行之前有全0行
				{
					// 将所有全0行的row_first值设置为node_num
					for (j = 0; j < (i / col - (last_row_num+1)); ++j)
					{
						s_matrix->row_first[i/col-j-1] = node_num;
					}
				}
				// 行号发生变化说明是新的一行开始,记录新的一行首元素的nodes索引。
				s_matrix->row_first[i/col] = node_num;
				last_row_num = i / col;
			}
			++node_num;
		}
	}

	// 最后几行可能出现连续全0行，需要将这些行的row_first值都设置为node_num
	for (i = row; i >= 0; --i)
	{
		if (s_matrix->row_first[i] == -1)
			s_matrix->row_first[i] = node_num;
		else
			break;
	}

	s_matrix->node_num = node_num;
	return;
}


/**********************************************
* function: 实现一个稀疏矩阵的转置运算
* author: Herbert
* date: 2019-12-27
**********************************************/
Sparse_matrix * sparse_matrix_transpose (Sparse_matrix * s_matrix)
{
	if (NULL == s_matrix)
		return NULL;
	Sparse_matrix *trans_matrix = (Sparse_matrix*) malloc (sizeof (Sparse_matrix));	
	if (NULL == trans_matrix)
		return NULL;
	trans_matrix->row = s_matrix->col;
	trans_matrix->col = s_matrix->row;
	trans_matrix->node_num = s_matrix->node_num;

	int i,j;
	int node_pos = 0;
	for (i = 0; i < s_matrix->node_num; ++i)
	{
		node_pos = 0;
		for (j = 0; j < s_matrix->node_num; ++j)
		{
			if (i == j)
				continue;
			if (s_matrix->nodes[i].c_idx > s_matrix->nodes[j].c_idx)
			{
				++node_pos;
			}
			else if (s_matrix->nodes[i].c_idx == s_matrix->nodes[j].c_idx)
			{
				if (s_matrix->nodes[i].r_idx > s_matrix->nodes[j].r_idx)
					++node_pos;
			}
			else
			{
				// do nothing;
			}
		}
		trans_matrix->nodes[node_pos].r_idx = s_matrix->nodes[i].c_idx;
		trans_matrix->nodes[node_pos].c_idx = s_matrix->nodes[i].r_idx;
		trans_matrix->nodes[node_pos].value = s_matrix->nodes[i].value;
	}
	return trans_matrix;
}

/**********************************************
* function: 实现一个稀疏矩阵的转置运算(优化方法)
* author: Herbert
* date: 2019-12-27 严蔚敏视频14前10分钟
**********************************************/
Sparse_matrix * optimize_sparse_matrix_transpose (Sparse_matrix *s_matrix)
{
	if (NULL == s_matrix)
		return NULL;
	Sparse_matrix *trans_matrix = (Sparse_matrix*) malloc (sizeof (Sparse_matrix));	
	if (NULL == trans_matrix)
		return NULL;
	trans_matrix->row = s_matrix->col;
	trans_matrix->col = s_matrix->row;
	trans_matrix->node_num = s_matrix->node_num;
	int i,node_pos;
	// 求原矩阵中每列元素个数并记录在数组中
	int *col_num = (int *)malloc (s_matrix->col * sizeof (int));
	if (col_num == NULL)
		return NULL;
	for (i = 0; i < s_matrix->node_num; ++i)
	{
		col_num[s_matrix->nodes[i].c_idx]++;
	}

	// 求原矩阵中每列首元素（对应转置矩阵每行首元素）在转置存储结构中的位置
	int *row_first_pos = (int*)malloc (s_matrix->col * sizeof (int));
	if (row_first_pos == NULL)
		return NULL;
	row_first_pos[0] = 0;
	for (i = 1; i < s_matrix->col; ++i)
	{
		row_first_pos[i] = row_first_pos[i-1] + col_num[i-1];
	}
	
	// 遍历原矩阵，将每个node放入转置矩阵的对应位置
	for (i = 0; i < s_matrix->node_num; ++i)
	{	
		node_pos = row_first_pos[s_matrix->nodes[i].c_idx];
		trans_matrix->nodes[node_pos].r_idx = s_matrix->nodes[i].c_idx;
		trans_matrix->nodes[node_pos].c_idx = s_matrix->nodes[i].r_idx;
		trans_matrix->nodes[node_pos].value = s_matrix->nodes[i].value;
		row_first_pos[s_matrix->nodes[i].c_idx]++;
	}

	free (col_num);
	free (row_first_pos);
	return trans_matrix;
}


/**********************************************
* function: 增加接口以用户输入的行列号给用户返回一个指定的稀疏矩阵
* author: Herbert
* param: s_matrix: 生成的稀疏矩阵 row: 行数 col:列数
* date: 2019-12-28
* comment: 生成节点-> 把节点放入普通存储结构 -> 由普通存储结构转为稀疏矩阵存储结构
**********************************************/
Sparse_matrix *get_specific_sparse_matrix (Sparse_matrix **s_matrix, int row, int col)
{
	if (NULL == s_matrix) 
		return NULL;
	Sparse_matrix *sparse_matrix = NULL;
	if ( NULL == (sparse_matrix = create_sparse_matrix (s_matrix)) )
		return NULL;
	int i = 0;
	int r_idx,c_idx,value;
	sparse_matrix->row = row;
	sparse_matrix->col = col;
	sparse_matrix->node_num = (row * col) / 10 + 3; 
	
	int *normal_dim_array = (int*)malloc (sizeof (int)*row*col);
	if (NULL == normal_dim_array)
		return NULL;

	memset (normal_dim_array, 0, sizeof(int)*row*col);
	// 生成稀疏矩阵的非零元素
	while (i < sparse_matrix->node_num)
	{
		r_idx = rand () % row;
		c_idx = rand () % col;
		value = (rand () % 9) + 1; // 每个节点数值在1 ~ 9
		if (normal_dim_array[r_idx*col+c_idx] != 0)
		{
			//此位置已经生成过元素，则重新生成
			continue;
		}
		else
		{
			normal_dim_array[r_idx*col+c_idx] = value;
			++i;
		}
	}

	// 根据普通矩阵的表达形式生成稀疏矩阵的表达	
	get_sparse_matrix_from_normal_matrix (normal_dim_array, row, col, sparse_matrix);
	
	free (normal_dim_array);

	*s_matrix = sparse_matrix;
	return *s_matrix;
}

/**********************************************
* function: 求稀疏矩阵的乘积
* author: Herbert
* param: m_matrix: 稀疏矩阵m  n_matrix: 稀疏矩阵n
* date: 2019-12-29
* comment: Q[i][j] += M[i][k] * N[k][j];
**********************************************/
Sparse_matrix* multiply_sparse_matrix (Sparse_matrix *m_matrix, Sparse_matrix *n_matrix)
{
	if (NULL == m_matrix || NULL == n_matrix)
		return NULL;
	if (m_matrix->col != n_matrix->row)
	{
		printf ("error: M matrix col != N matrix row\n");
		return NULL;
	}
	Sparse_matrix *ret_sparse = NULL;
	if ( NULL == (ret_sparse = create_sparse_matrix (&ret_sparse)) )
		return NULL;
	ret_sparse->row = m_matrix->row;
	ret_sparse->col = n_matrix->col;
	
	int cur_node = 0; // 当前处理的m矩阵的非零节点
	int i,j;
	int cur_row; // 当前处理的m矩阵节点的行坐标
	int cur_col; // 当前处理的m矩阵节点的列坐标
	int rst_non_zero = 0; // 结果中非零元素个数
	int *add_value_arr = (int*)malloc (sizeof(int)*n_matrix->col);
	if (NULL == add_value_arr)
		return NULL;
	while (cur_node < m_matrix->node_num)
	{
		memset (add_value_arr, 0, sizeof(int)*n_matrix->col);
		cur_row = m_matrix->nodes[cur_node].r_idx;

		// 遍历m矩阵行号相同的所有node节点
		for (i = m_matrix->row_first[cur_row]; i < m_matrix->row_first[cur_row+1] ;++i)
		{
			// 对于m矩阵中某一个m_node，在n矩阵中找n->row=m->col的所有节点，将其乘积累加到add_value_arr中。
			cur_col = m_matrix->nodes[cur_node].c_idx;
			for (j = n_matrix->row_first[cur_col]; j < n_matrix->row_first[cur_col+1]; ++j)
			{
				add_value_arr[n_matrix->nodes[j].c_idx] += m_matrix->nodes[i].value * n_matrix->nodes[j].value;
			}
			++cur_node;
		}

		// 从add_value_arr中取出所有非零元素,将其存入到结果矩阵ret_sparse中
		for (i = 0; i < n_matrix->col; ++i)
		{
			if (0 != add_value_arr[i])
			{
				ret_sparse->nodes[rst_non_zero].r_idx = cur_row;
				ret_sparse->nodes[rst_non_zero].c_idx = i;
				ret_sparse->nodes[rst_non_zero].value = add_value_arr[i];
				++rst_non_zero;
			}
		}
	}

	ret_sparse->node_num = rst_non_zero;

	return ret_sparse;
}


/**********************************************
* function: 以经典方式打印稀疏矩阵
* author: Herbert
* param: s_matrix: 稀疏矩阵
* date: 2019-12-29
* comment: 
**********************************************/
void print_sparse_matrix_classic (Sparse_matrix *s_matrix)
{
	if (NULL == s_matrix)
		return;

	int i;
	int r_idx = 0;
	int c_idx = 0;
	int val;
	for (i = 0; i < s_matrix->row*s_matrix->col; ++i)
	{
		r_idx = i / s_matrix->col;
		c_idx = i % s_matrix->col;

		if (c_idx == 0)
			printf ("\n");
		if (is_matrix_node_exist (s_matrix, r_idx, c_idx, &val))
		{
			printf ("%2d ", val);
		}
		else
		{
			printf ("%2d ", 0);
		}
	}
	return ;
}


int main (void)
{
	srand (time(NULL));
#if 0
	int arr[ROW*COL] = {0};
	
	// 初始化二维数组元素值
	init_two_dimensional_array (arr);

	printf ("\nsrc matrix is: \n");	
	print_two_dimensional_array (arr, ROW, COL);

	// 使用普通方式计算matrix的转置
	int *transpose_arr = matrix_transpose (arr, ROW, COL);
	printf ("\ntranspose matrix is:\n");
	print_two_dimensional_array (transpose_arr, COL, ROW);

	Sparse_matrix *s_matrix = NULL;
	create_sparse_matrix (&s_matrix);

	// 从普通矩阵表示法得到稀疏矩阵表示结构
	get_sparse_matrix_from_normal_matrix (arr, ROW, COL, s_matrix);
	print_sparse_matrix (s_matrix);
	
	// 自己实现的稀疏矩阵转置
	Sparse_matrix *transpos_matrix = sparse_matrix_transpose (s_matrix);
	print_sparse_matrix (transpos_matrix);

	// 根据严蔚敏方法实现的稀疏矩阵转置运算
	Sparse_matrix *opti_transpose_matrix = optimize_sparse_matrix_transpose (s_matrix);
	print_sparse_matrix (opti_transpose_matrix);

	free (opti_transpose_matrix);
	free (transpos_matrix);
	free (s_matrix);
#endif
	Sparse_matrix *m_sparse_matrix = NULL;
	get_specific_sparse_matrix (&m_sparse_matrix, 14, 12);
	print_sparse_matrix_classic (m_sparse_matrix);
	print_sparse_matrix (m_sparse_matrix);

	Sparse_matrix *n_sparse_matrix = NULL;
	get_specific_sparse_matrix (&n_sparse_matrix, 12, 18);
	print_sparse_matrix_classic (n_sparse_matrix);
	print_sparse_matrix (n_sparse_matrix);

	Sparse_matrix *multiple_matrix = multiply_sparse_matrix (m_sparse_matrix, n_sparse_matrix);
	print_sparse_matrix_classic (multiple_matrix);
	print_sparse_matrix (multiple_matrix);

	free (multiple_matrix);
	free (n_sparse_matrix);
	free (m_sparse_matrix);
	return 0;
}
