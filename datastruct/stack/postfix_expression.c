#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* 本程序利用栈求得运算式的后缀形式，并根据其后缀形式求值 */
/* 本程序假定输入的运算式都是合法的,数字只有一位不能处理多位数字 */

/* 编译运行方法
compile: gcc postfix_expression.c stack.c

hanb@:stack$ ./a.out 
Input the expression (End with '#'): 1 * 2 + (3-9 / 2) * 2   #
postfix expression is: 12*392/-2*+#
Calculation result is : -1.000000.
*/

/****************************************************
 * function: 获取键盘输入的表达式字串
 * author: herbert
 * date: 2019-12-10
 ****************************************************/
void get_input (char *out)
{
	int idx = 0;
	char ch;
	while ( ( ch = getchar () ) != EOF)
	{
		if (ch == '\r' || ch == '\n')
			break;
		out[idx++] = ch;
	}
	return;
}

/****************************************************
 * function: 判断是否是操作符，#也看作操作符
 * author: herbert
 * date: 2019-12-10
 ****************************************************/
BOOL is_operator (char c)
{
	return ( (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '#') );
}

/****************************************************
 * function: 判断操作符优先级
 * author: herbert
 * date: 2019-12-10
 * common: 第一个操作数是否比第二个操作数优先级高
 ****************************************************/
BOOL is_priority_higher (char first_op, char second_op)
{
	return (	
				( '#' != first_op && ('#' == second_op || '(' == second_op) ) ||
				( ( first_op == '*' || first_op == '/' ) && ( second_op == '+'  || second_op == '-') )
		   );
}

/****************************************************
 * function: 获取一个表达式的后缀形式
 * author: herbert
 * date: 2019-12-10
 * common: result中存放后缀式
 ****************************************************/
int get_postfix_expression (const char *ori_expression, char *result)
{
	if (NULL == ori_expression || NULL == result)
	{
		printf ("invalid params\n");
		return -1;
	}

	int rst_idx = 0;

	Stack *stack_op = NULL;
	init_stack (&stack_op); // 初始化运算符栈

	char push_ch = '#';
	char pop_ch = 0;
	char top_ch = 0;
	push (stack_op, &push_ch, sizeof (char)); // 栈底压入#表示最低优先级的运算符
	
	const char *p = ori_expression;

	while ('#' != *p)
	{
		if (' ' == *p || '\t' == *p)
		{
			++p;
			continue;
		}
		if (!is_operator(*p)) // 不是操作符号
		{
			if ( '(' == *p ) // 左括号入栈
			{
				push_ch = '(';
				push (stack_op, &push_ch, sizeof (char));
			}
			else if ( ')' == *p)  // 遇到右括号则出栈直到左括号
			{
				pop (stack_op, &pop_ch, sizeof (char));
				while ('(' != pop_ch)
				{
					result[rst_idx++] = pop_ch;
					pop (stack_op, &pop_ch, sizeof (char));
				}
			}
			else
				result[rst_idx++] = *p;
		}
		else // 是操作符
		{
			get_top (stack_op, &top_ch, sizeof (char));
			while (!is_priority_higher (*p, top_ch)) // 将当前栈中优先级高于*p的操作符全部出栈放入result
			{
				pop (stack_op, &pop_ch, sizeof (char));
				result[rst_idx++] = pop_ch;
				get_top (stack_op, &top_ch, sizeof (char));
			}
			if (is_priority_higher (*p, top_ch)) // 优先级高于栈顶元素则入栈
			{
				push (stack_op, (const void*)p, sizeof (char));
			}
		}
		++p;
	}
	// 读到表达式结束的最后一个# 将栈中非#操作符号全部pop存入result
	while (!is_empty (stack_op))
	{
		pop (stack_op, &pop_ch, sizeof (char));
		if ('#' != pop_ch)
			result[rst_idx++] = pop_ch;
	}
	result[rst_idx] = '#';

	clear_stack (stack_op);
	return 0;
}

/****************************************************
 * function: 根据操作符计算结果
 * author: herbert
 * date: 2019-12-10
 * common: ab*cde/-f*+
 ****************************************************/
float get_value (float first_val, float second_val, char op)
{
	switch (op)
	{
		case '+':
			return first_val + second_val;
		case '-':
			return first_val - second_val;
		case '*':
			return first_val * second_val;
		case '/':
			return first_val / second_val;
		default:
			printf ("get_value: invalid op\n");
			exit (-1);
	}
}

/****************************************************
 * function: 根据后缀表达式求值
 * author: herbert
 * date: 2019-12-10
 * common: ab*cde/-f*+
 ****************************************************/
int get_value_by_postfix_expression (const char *post_ex, float *ret)
{
	if (NULL == post_ex || NULL == ret)
		return -1;
	Stack *stack = NULL;
	init_stack (&stack);
	const char *p = post_ex;
	float push_val = 0.0;
	float first_op_val = 0.0;
	float second_op_val = 0.0;
	float temp_ret = 0.0;
	while (*p != '#')
	{
		if (!is_operator(*p))
		{
			push_val = (*p - '0') * 1.0;
			push (stack, &push_val, sizeof(float));
		}
		else
		{
			if (stack->top < 1)
			{
				printf ("invalid postfix expression\n");
				return -1;
			}
			pop (stack, &second_op_val, sizeof (float));
			pop (stack, &first_op_val, sizeof (float));
			temp_ret = get_value (first_op_val, second_op_val, *p);
			push (stack, &temp_ret, sizeof (float));
		}
		++p;
	}

	// 最终的结果就是栈顶唯一的元素，取出它到ret
	pop (stack, ret, sizeof (float));
	return 0;
}

int main (int argc, char* argv[])
{
	printf ("Input the expression (End with '#'): ");
	char input_str[100] = {0};
	get_input (input_str);
	char postfix_expression [100] = {0};
	get_postfix_expression (input_str, postfix_expression);
	printf ("postfix expression is: %s\n", postfix_expression);
	float result = 0.0;
	get_value_by_postfix_expression (postfix_expression, &result);
	printf ("Calculation result is : %f.\n", result);
	return 0;
}



