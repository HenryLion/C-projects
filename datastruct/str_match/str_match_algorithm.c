#include <stdio.h>
#include <string.h>
#include <assert.h>

/* 本程序实现字符串匹配算法 */
 
 /*******************************************
  * function: 在串s中查找串t出现的位置
  * date: 2019-12-18
  * common: 自己实现的简单版本
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

/*******************************************
* function: 在串s中查找串t出现的位置
* date: 2019-12-18
* common: 严蔚敏-简单算法
******************************************/
int simple_str_match (const char *s, const char *t)
{
	if (NULL == s || NULL == t)
		return -1;
	int len_s = strlen (s);
	int len_t = strlen (t);
	if (len_s < len_t || len_s == 0 || len_t == 0)
		return -1;
	int i = 0; 
	int j = 0;
	while (i < len_s && j < len_t)
	{
		if (s[i] == t[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == len_t)
		return i - len_t;
	else
		return -1;
}


/*******************************************
* function: 在串s中查找串t出现的位置
* date: 2019-12-18
* common: 严蔚敏-首位匹配算法,对简单算法的优化,先比较首位字符相等的情况下再依次比较中间字符
******************************************/
int optimize_simple_str_match (const char *s, const char *t)
{
	if (NULL == s || NULL == t)
		return -1;
	int len_s = strlen (s);
	int len_t = strlen (t);
	if (len_s < len_t || len_s == 0 || len_t == 0)
		return -1;
	
	int i = 0;
	int j = 0;
	while (i <= len_s - len_t)
	{
		if (s[i] == t[j])
		{
			// 首字符相等
			if (s[i+len_t-1] == t[len_t-1])
			{
				// 末字符相等
				while (j < len_t - 2) // t串中间的字符还有len_t-2个字符需要比较
				{
					// 首末字符都相等则依次比较中间字符
					if (s[i+j+1] == t[j+1])
					{
						//如果相等则继续比较下一个字符
						j++;
						if (j == len_t - 2)
							return i;
					}
					else
					{
						// 如果中间字符出现不相等的情况则回溯
						++i;
						j = 0;
						break;
					}
				}
				return i; // 中间没有需要比较的字符则返回i位置
			}
			else
			{
				// 末字符不相等则回溯
				++i;
				j = 0;
			}
		}
		else
		{
			// 首字符不相等则回溯
			++i;
			j = 0;
		}
	}
	return -1;
}



void unit_test ()
{
	assert (-1 == my_get_substring_pos ("hello,world", ""));
	assert (-1 == my_get_substring_pos ("", "a"));
	assert (-1 == my_get_substring_pos ("hello", "hello,"));
	assert (-1 == my_get_substring_pos ("", ""));
	assert (-1 == my_get_substring_pos ("hello,world", "t"));
	assert (0 == my_get_substring_pos ("hello", "hello"));
	assert (1 == my_get_substring_pos (";jk,.", "jk,"));
	assert (5 == my_get_substring_pos ("hello, world", ", wor"));
	assert (10 == my_get_substring_pos ("hello, world", "ld"));
	assert (2 == my_get_substring_pos ("hello,world", "l"));
	assert (58 == my_get_substring_pos ("zhonghuarenmin gonghe guo ,zhongyang renmin zhengfu,zai jintian chegnli le !", "nt"));

	assert (-1 == simple_str_match ("hello,world", ""));
	assert (-1 == simple_str_match ("", "a"));
	assert (-1 == simple_str_match ("hello", "hello,"));
	assert (-1 == simple_str_match ("", ""));
	assert (-1 == simple_str_match ("hello,world", "t"));
	assert (0 == simple_str_match ("hello", "hello"));
	assert (1 == simple_str_match (";jk,.", "jk,"));
	assert (5 == simple_str_match ("hello, world", ", wor"));
	assert (10 == simple_str_match ("hello, world", "ld"));
	assert (2 == simple_str_match ("hello,world", "l"));
	assert (58 == simple_str_match ("zhonghuarenmin gonghe guo ,zhongyang renmin zhengfu,zai jintian chegnli le !", "nt"));

	assert (-1 == optimize_simple_str_match ("hello,world", ""));
	assert (-1 == optimize_simple_str_match ("", "a"));
	assert (-1 == optimize_simple_str_match ("hello", "hello,"));
	assert (-1 == optimize_simple_str_match ("", ""));
	assert (-1 == optimize_simple_str_match ("hello,world", "t"));
	assert (0 == optimize_simple_str_match ("hello", "hello"));
	assert (1 == optimize_simple_str_match (";jk,.", "jk,"));
	assert (5 == optimize_simple_str_match ("hello, world", ", wor"));
	assert (1 == optimize_simple_str_match ("rld", "ld"));
	assert (2 == optimize_simple_str_match ("hello,world", "l"));
	assert (58 == optimize_simple_str_match ("zhonghuarenmin gonghe guo ,zhongyang renmin zhengfu,zai jintian chegnli le !", "nt"));

	printf ("test OK!\n");
}

int main (void)
{
	unit_test ();
	return 0;
}




