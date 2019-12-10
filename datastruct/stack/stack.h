#ifndef _STACK_H_
#define _STACK_H_

typedef void * Stack_node;
typedef unsigned char BOOL;

#define INIT_STACK_LEN  100
#define TRUE  1
#define FALSE 0

typedef enum op_status
{
	ERROR = -1,
	OK = 0
} OP_STATUS;

typedef struct Stack_t
{
	int top;
	Stack_node node_array[INIT_STACK_LEN];
} Stack;

/* function defination */
Stack* init_stack (Stack **);
BOOL is_empty (Stack *stack);
BOOL is_full (Stack *stack);
OP_STATUS push (Stack *stack, void *data, int data_size);
OP_STATUS pop (Stack *stack, void *buff, int data_size);
OP_STATUS get_top (Stack *stack, void *buff, int data_size);
void clear_stack (Stack *stack);
#endif
