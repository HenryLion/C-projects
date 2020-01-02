#ifndef _CROSS_LIST_MATRIX_H_
#define _CORSS_LIST_MATRIX_H_

#define MAX_ROW 50
#define MAX_COL 50
#define INVALID_DATA 0xFFFFFFFF

typedef unsigned char BOOL;
#define TRUE  1
#define FALSE 0

typedef struct matrix_node
{
	int r_idx;
	int c_idx;
	int value;
	struct matrix_node* row_next;
	struct matrix_node* col_next;
} matrix_node_t;

typedef struct matrix
{
	int node_num;
	int row_num;
	int col_num;
	matrix_node_t *row_head[MAX_ROW];
	matrix_node_t *col_head[MAX_COL];
} Matrix;

#endif
