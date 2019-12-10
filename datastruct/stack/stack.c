#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/* 本程序试图实现一个通用的栈结构 */

/****************************************************
 * function: 初始化栈栈顶指向栈底元素
 * author: herbert
 * date: 2019-12-10
 ****************************************************/
Stack* init_stack (Stack **stack)
{
	if (NULL == stack)
		return NULL;
	*stack = (Stack *)malloc (sizeof (Stack));
	if (NULL == *stack)
		return NULL;
	(*stack)->top = -1;
	int i;
	for (i = 0; i < INIT_STACK_LEN; ++i)
	{
		(*stack)->node_array[i] = NULL;
	}
	return *stack;
}


/****************************************************
 * function: 判断栈是否为空
 * author: herbert
 * date: 2019-12-10
 ****************************************************/
BOOL is_empty (Stack *stack)
{
	if (NULL == stack)
	{
		printf ("operate no init stack\n");
		exit (-1);
	}
	return (stack->top == -1);
}

/****************************************************
 * function: 判断栈满
 * author: herbert
 * date: 2019-12-10
 ****************************************************/
BOOL is_full (Stack *stack)
{
	if (NULL == stack)
	{
		printf ("operate no init stack\n");
		exit (-1);
	}
	return ( stack->top == (INIT_STACK_LEN - 1) );
}

/****************************************************
 * function: 入栈
 * author: herbert
 * date: 2019-12-10
 ****************************************************/
OP_STATUS push (Stack *stack, void *data, int data_size)
{
	if (!is_full (stack))
	{
		stack->top += 1;
		stack->node_array[stack->top] = (void *)malloc (data_size);
		if (NULL == stack->node_array[stack->top])
			return ERROR;
		memcpy (stack->node_array[stack->top], data, data_size);
	}
	else
	{
		return ERROR;
	}
	return OK;
}



/****************************************************
 * function: 出栈
 * author: herbert
 * date: 2019-12-10
 ****************************************************/
OP_STATUS pop (Stack *stack, void *buff, int data_size)
{
	if (NULL == buff)
		return ERROR;
	if (!is_empty (stack))
	{
		memcpy (buff, stack->node_array[stack->top], data_size);
		free (stack->node_array[stack->top]);
		stack->node_array[stack->top] = NULL;
		stack->top -= 1;
	}
	else
	{
		return ERROR;
	}
	return OK;
}


/****************************************************
 * function: 获取栈顶元素
 * author: herbert
 * date: 2019-12-10
 ****************************************************/
OP_STATUS get_top (Stack *stack, void *buff, int data_size)
{
	if (NULL == buff)
		return ERROR;
	if (!is_empty (stack))
	{
		memcpy (buff, stack->node_array[stack->top], data_size);
	}
	else
	{
		return ERROR;
	}
	return OK;
}
	

/****************************************************
 * function: 释放栈
 * author: herbert
 * date: 2019-12-10
 ****************************************************/
void clear_stack (Stack *stack)
{
	if (NULL == stack)
		return;
	int i = 0;
	for (i = stack->top; i >= 0; --i)
	{
		free (stack->node_array[i]);
		stack->node_array[i] = NULL;
	}
	free (stack);
	stack = NULL;
}	
