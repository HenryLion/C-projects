#include <stdio.h>
#include <string.h>

/* 本程序实现字符串匹配算法 */
 
 /*******************************************
  * function: 在串s中查找串t出现的位置
  * date: 2019-12-18
  * 
  ******************************************/
int my_get_substring_pos (const char *s, const char *t)
{
	if (NULL == s || NULL == t)
		return -1;
	int len_s = strlen (s);
	int len_t = strlen (t);
	if (len_s < len_t || len_s == 0 || len_t == 0)
		return -1;
	
	int s_beg_cmp_pos = 0;
	int t_idx = 0;
	int s_idx = 0;

	while (s_beg_cmp_pos <= (len_s-len_t))
	{
		s_idx = s_beg_cmp_pos;
		while (t_idx < len_t)
		{
			if (s[s_idx] == t[t_idx])
			{
				++s_idx;
				++t_idx;
			}
			else
			{
				++s_beg_cmp_pos;
				t_idx = 0;
				break;
			}
		}
		if (t_idx == len_t)
			return s_beg_cmp_pos;

	}

	return -1;
}

int main (void)
{
	printf ( "pos is: %d\n", my_get_substring_pos ("hello,world", "t") );
	return 0;
}




