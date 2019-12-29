#ifndef _SPARSE_ARRAY_H_
#define _SPARSE_ARRAY_H_

#define ROW 5
#define COL 8
#define MAX_NONZERO_NODE_NUM 200  // 按照稀疏矩阵的定义,若有200个非零元则支持的最大总元素个数为200/(5/100) = 4000
#define MAX_NODE_VALUE 65535
/* 本程序实现的是稀疏数组的有效表示方法 */
/* 稀疏矩阵需要考虑到存储空间的节省和计算时间的节约 */

typedef struct matrix_node
{
	int r_idx; // 稀疏矩阵非零元的行标
	int c_idx; // 稀疏矩阵非零元的列标
	int value; // 稀疏矩阵非零元的值
} matrix_node_t;

typedef struct sparse_matrix
{
	int row;  // 稀疏矩阵行数
	int col;  // 稀疏矩阵列数
	int node_num; // 稀疏矩阵非零元个数
	matrix_node_t nodes[MAX_NONZERO_NODE_NUM]; // 存储非零元节点
    int row_first[MAX_NONZERO_NODE_NUM];  // 每行首元素在nodes中的位置
} Sparse_matrix;

#endif
