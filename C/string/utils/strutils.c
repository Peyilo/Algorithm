//
// Created by Anvei on 2022/10/12.
//
#include "../../utils/errorutils.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

/**
 * 有给定的字符串解析其double值
 * @param expr
 * @return
 */
double parse_double(const char *expr)
{
    double res = 0;
    int len = (int) strlen(expr);
    bool negative = false;
    bool flag = true;
    int dot_pos = -1;
    bool dot_flag = false;
    for (int i = 0; i < len; i++)           // 从左到右依次扫描字符，查找小数点的位置同时，确定是否有负号
    {
        char ch = *(expr + i);
        if (flag && ch == '-')
        {
            flag = false;
            negative = true;
            continue;
        }
        else if (isdigit(ch))
        {
            continue;
        }
        else if (ch == '.' && !dot_flag)
        {
            dot_pos = i;
            dot_flag = true;
        }
        else                    // 数字字符串内只允许首字符出现负号、至多一个小数点、数字字符
        {                       // 其他情况皆为非法数字字符串
            anv_error("该字符串表达式存在非法字符!");
        }
    }

    if (!dot_flag) dot_pos = len;           // 如果没有小数点，就将小数点位置定义在最后以为数字字符的下一位

    for (int i = negative; i < dot_pos; i++)    // negative为true表示该数字为负数，首字符为负号，需要跳过，反之，无需跳过
        res += (*(expr + i) - '0') * pow(10, dot_pos - i - 1);
    for (int i = dot_pos + 1; i < len; i++)
        res += (*(expr + i) - '0') * pow(10, dot_pos - i);

    return negative ? -res : res;
}