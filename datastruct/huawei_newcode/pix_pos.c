#include <stdio.h>
#include <string.h>
/* 坐标移动 */
int is_number (char ch)
{
    return (ch >= '0' && ch <= '9');
}
 
int is_valid_dir_ch (char ch)
{
    return (ch == 'A' || ch == 'D' || ch == 'W' || ch == 'S');
}
 
int is_valid (char *str)
{
    int len = strlen (str);
    int i;
    if (len != 2 && len != 3)
    {
         return 0;
    }
 
    if (str[0] != 'A' && str[0] != 'D' && str[0] != 'W' && str[0] != 'S')
    {
          return 0;     
    }
 
    for (i = 1; i < len; ++i)
    {
        if (!is_number(str[i]))
        {         
            return 0;
        }
    }
    return 1;
}
 
void cacl_pix (char *one_pix, int *x_pos, int *y_pos)
{
    int off_val = 0;
    if (!is_valid (one_pix))
    {
         return;      
    }
 
    char *p = one_pix + 1;
    while (*p != '\0' && is_number (*p))
    {
        off_val = off_val * 10 + (*p - '0');
        ++p;
    }
     
    switch (one_pix[0])
    {
        case 'A':
            *x_pos -= off_val;
            break;
        case 'D':
            *x_pos += off_val;
            break;
        case 'W':
            *y_pos += off_val;
            break;
        case 'S':
            *y_pos -= off_val;
            break;
        default:
            break;
    }
    return;
}
 
int main (void)
{
    int x_pos = 0;
    int y_pos = 0;
    char input[3000] = {0};
    char *p = NULL;
    char *beg = NULL;
    char *end = NULL;
    char one_pix[5] = {0};
    int one_pix_num = 0;
    while (fgets (input, 3000, stdin) != NULL)
    {
		x_pos = 0;
		y_pos = 0;
        if (input[strlen(input)-1] == '\n')
            input[strlen(input)-1] = '\0';
        p = input;
        beg = input;
        while (*p != '\0')
        {
            while (!is_valid_dir_ch(*beg) && *beg != '\0')  /* 此循环保证跳到下一个有效坐标位置的头 */
            {
                while (*beg != ';')
                {
                    ++beg;
                }
                ++beg;
            }
            if (*beg == '\0')
                break;

            memset (one_pix, 0, 5);
            one_pix_num = 0;
            end = beg;
            while (*end != ';')
            {
                one_pix[one_pix_num++] = *end;
                ++end;               
            }
            one_pix[one_pix_num] = '\0';
            cacl_pix (one_pix, &x_pos, &y_pos);
            p = end+1;
            beg = end+1;

        }
        printf ("%d,%d\n", x_pos, y_pos);     
        memset (input, 0, 3000);
    }

    return 0;
}
