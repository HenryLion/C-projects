#include <stdio.h>
#include "stack.h"

typedef struct point
{
	int x;
	int y;
} Point;

int main (void)
{
	Stack *stack = NULL;


	/* 栈用来存储整数  */
	init_stack (&stack);

	int interger;

	// 输入1 2 3 4 5 6 7 8 -1
	// 输出8 7 6 5 4 3 2 1 
	while (1)
	{
		scanf ("%d", &interger);
		if (0 > interger) //取一个输入终止条件
			break;

		push (stack, &interger, sizeof (int));
	}

	while (!is_empty (stack))
	{
		pop (stack, &interger, sizeof(int));
		printf ("%d ", interger);
	}
	printf ("\n");
	
	/* 销毁整数栈 */
	clear_stack (stack);

	/* 栈用来存储Point结构 */
	init_stack (&stack);

	Point pt;
	// 输入1,2 2,3 3,4 4,5 5,6 6,7 7,8 8,9 -1,2
	// 输出(8,9) (7,8) (6,7) (5,6) (4,5) (3,4) (2,3) (1,2)
	while (1)
	{
		scanf ("%d,%d", &pt.x, &pt.y);
		if (0 > pt.x)
			break;
		push (stack, &pt, sizeof (Point));
	}

	while (!is_empty (stack))
	{
		pop (stack, &pt, sizeof (Point));
		printf ("(%d,%d) ", pt.x, pt.y);
	}
	printf ("\n");
	clear_stack (stack);

	return 0;
}
	
