#include <stdio.h>

/* 本程序试图实现一个通用的栈结构 */

typedef void * Stack_node;

#define INIT_STACK_LEN  100

typedef struct Stack_t
{
	int top;
	Stack_node node_array[INIT_STACK_LEN];
} Stack;

Stack stack;

Stack_node create_stack (int data_size)
{



