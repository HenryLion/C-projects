#include <string.h>
#include <stdio.h>
#include "stack.h"
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/* 本程序的主要目的是进行括号匹配的判断  */


/* gcc -o bracket_match bracket_match.c stack.h stack.c
 * ./bracket_match argv[1]
 */


// 判断是不是左括号
BOOL is_left_brackets (char ch)
{
	return ( ( ch == '(') ||
	         ( ch == '[') ||
			 ( ch == '{') );
}

// 判断是不是右括号
BOOL is_right_brackets (char ch)
{
	return ( (ch == ')') ||
	         (ch == ']') ||
			 (ch == '}') );
}

// 判断两个括号是否匹配
BOOL is_a_bracket_pair (char l_b, char r_b)
{
	return ( (l_b == '(' && r_b == ')') || 
	         (l_b == '[' && r_b == ']') ||
			 (l_b == '{' && r_b == '}')
		   );
}

// 判断一个字符串中包含的所有括号是否匹配
BOOL is_brackets_match (char *str)
{
	BOOL result = TRUE;
	if (NULL == str)
		return 0;
	char *p = str;
	char pop_val;

	Stack *stack = NULL;
	init_stack (&stack);

	while (*p != '\0')
	{
		if (is_left_brackets(*p))
		{
			push (stack,p,sizeof(char));
		}
		else if (is_right_brackets(*p))
		{
			if (is_empty(stack))
			{
				result = FALSE;
				goto OVER;
			}
			else
			{
				pop (stack, &pop_val, sizeof(char));
				if (is_a_bracket_pair (pop_val, *p))
				{
				}
				else
				{
					result = FALSE;
					goto OVER;
				}
			}
		}
		else
		{
			++p;
			continue;
		}
		++p;
	}
	if (!is_empty(stack))
	{
		result = FALSE;
		goto OVER;
	}
	result = TRUE;
OVER:
	clear_stack (stack);
	return result;
}

// 括号匹配的单元测试
void unit_test ()
{
	assert (is_brackets_match ("()") == 1);	
	assert (is_brackets_match ("[]") == 1);
	assert (is_brackets_match ("{}") == 1);
	assert (is_brackets_match ("([])") == 1);
	assert (is_brackets_match ("[()]") == 1);
	assert (is_brackets_match ("{()}") == 1);
	assert (is_brackets_match ("[[]]") == 1);
	assert (is_brackets_match ("[t[]]") == 1);
	assert (is_brackets_match (")") == 0);
	assert (is_brackets_match ("())") == 0);
	assert (is_brackets_match ("([)]") == 0);
	assert (is_brackets_match ("()[](") == 0);
	assert (is_brackets_match ("[[]]") == 1);
	printf ("test OK!\n");
}

// 判断运行参数argv[1]代表的文件中所有的括号是否匹配
int main (int argc, char *argv[])
{
	unit_test ();
	char *file_buf = NULL;
	int read_byte = 0;
	off_t filepos;

	if (2 != argc)
	{
		printf ("Usage: ./a.out filename\n");
		return -1;
	}
	int fd = open (argv[1], O_RDONLY);
	if (-1 == fd)
	{
		printf ("open file bracket_file error!\n");
		return -1;
	}
	
	filepos = lseek (fd, 0, SEEK_END);
	lseek (fd, 0, SEEK_SET);
	file_buf = (char*)malloc ( (int)filepos+1);
	if (NULL == file_buf)
	{
		printf ("malloc error!\n");
		return -1;
	}
	if ( (read_byte == read (fd, file_buf, filepos)) < 0)
	{
		printf ("read file error!\n");
		free (file_buf);
		return -1;
	}
	
	if (is_brackets_match (file_buf))
	{
		printf ("program edit brackets OK!\n");
	}
	else
	{
		printf ("some brackets miss_match in program!\n");
	}
	free (file_buf);
	return 0;
}
