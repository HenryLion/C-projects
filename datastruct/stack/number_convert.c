#include <stdio.h>
#include "stack.h"

/* 本程序用实现的通用栈来实现数制转换  */
/* 十进制转八进制 */

int main (void)
{
	Stack *stack = NULL;
	if ( NULL == (stack = init_stack (&stack)) )
	{
		printf ("init_stack error\n");
		return -1;
	}

	int remainder = 0;
	int decimal_number = 0;
	int top_num = 0;
	while (1)
	{
		printf ("input the decimal number: ");
		scanf ("%d", &decimal_number);
		if (0 > decimal_number)
		{
			printf ("invalid number\n");
			return -1;
		}
		while (decimal_number > 0)
		{
			remainder = decimal_number % 8;
			push (stack, &remainder, sizeof (int));
			decimal_number /= 8;
		}

		printf ("Octal number is: ");
		while (!is_empty (stack))
		{
			pop (stack, &top_num, sizeof (int));
			printf ("%d",top_num);
		}
		printf ("\n");
	}
	clear_stack (stack);
	return 0;
}


