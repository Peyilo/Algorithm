//
// Created by Anvei on 2022/10/11.
//
#include "rpn_expression.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>

#define ANVEI_RPN_STACK_INITSIZE 20
#define ANVEI_RPN_STACK_INCREMENTSIZE 10
#define ANVEI_RPN_SEQLIST_INITSIZE 20
#define ANVEI_RPN_SEQLIST_INCREMENTSIZE 10
#define ANVEI_RPN_STRING_INCREMENT_SIZE 10

// 字符串实现
typedef struct {
    char *str;
    int len;
    int size;
} anvei_rpn_string;

// 字符串栈
typedef struct {
    anvei_rpn_string *base;
    anvei_rpn_string *top;
    int size;
} anvei_rpn_stack;
// 字符串顺序表
typedef struct {
    anvei_rpn_string *data;
    int length;
    int size;
} anvei_rpn_seqlist;

// 记录操作符及其优先级
static char operators[][2] = {{'+', '1'}, {'-', '1'},
                      {'*', '2'}, {'/', '2'},
                      {'^', '2'}};

/**
 * 为字符串指定下标设置一个字符
 * @param pstr
 * @param index
 * @param ch
 * @return 设置成功则返回true
 */
static bool anvei_rpn_str_set(anvei_rpn_string *pstr, int index, char ch)
{
    // 处理index错误情形
    if (pstr->len < index) return false;
    // 处理内存不够的情形
    if (pstr->size == index)
    {
        char *temp = realloc(pstr->str, sizeof(char) * (pstr->len + ANVEI_RPN_STRING_INCREMENT_SIZE));
        if (!temp) return false;
        pstr->str = temp;
        pstr->size += ANVEI_RPN_STRING_INCREMENT_SIZE;
    }
    *(pstr->str + index) = ch;
    pstr->len++;
    return true;
}

/**
 * 使用char *类型给字符串进行初始化
 * @param pstr
 * @param init_str
 * @return
 */
static bool anvei_rpn_str_init(anvei_rpn_string *pstr, const char *init_str)
{
    int len = (int) strlen(init_str);
    char *temp = malloc(sizeof(char) * len);
    if (!temp) return false;
    pstr->len = 0;
    pstr->size = len;
    pstr->str = temp;
    for (int i = 0; i < len; i++)
        anvei_rpn_str_set(pstr, i, *init_str++);
    return true;
}

/**
 * 指定字符串长度进行初始化
 * @param pstr
 * @param len
 * @return
 */
static bool anvei_rpn_str_init_by_size(anvei_rpn_string *pstr, int len)
{
    char *temp = malloc(sizeof(char) * len);
    if (!temp) return false;
    pstr->len = 0;
    pstr->size = len;
    pstr->str = temp;
    for (int i = 0; i < len; i++)
        *temp++ = '\0';
    return true;
}

/**
 * 销毁一个字符串
 * @param str
 */
static void anvei_rpn_str_destory(anvei_rpn_string str)
{
    free(str.str);
}

/**
 * 获取字符拆指定下标的字符
 * @param str
 * @param index
 * @return
 */
static char anvei_rpn_str_get(anvei_rpn_string str, int index)
{
    return *(str.str + index);
}

/**
 * 字符串拼接
 * @param a
 * @param b
 * @return
 */
static anvei_rpn_string anvei_rpn_str_add(anvei_rpn_string a, anvei_rpn_string b)
{
    anvei_rpn_string res;
    int len = a.len + b.len;
    anvei_rpn_str_init_by_size(&res, len);
    for (int i = 0; i < a.len; i++)
        anvei_rpn_str_set(&res, i, anvei_rpn_str_get(a, i));
    for (int i = a.len; i < len; i++)
        anvei_rpn_str_set(&res, i, anvei_rpn_str_get(b, i - a.len));
    return res;
}

/**
 * 初始化一个字符串栈
 * @param pstack
 * @return
 */
static bool anvei_rpn_stack_init(anvei_rpn_stack *pstack)
{
    anvei_rpn_string *pele = malloc(sizeof(anvei_rpn_string) * ANVEI_RPN_STACK_INITSIZE);
    if (!pele) return false;
    pstack->base = pele;
    pstack->top = pele;
    pstack->size = ANVEI_RPN_STACK_INITSIZE;
    return true;
}

/**
 * 销毁一个字符串栈
 * @param pstack
 */
static void anvei_rpn_stack_destory(anvei_rpn_stack *pstack)
{
    free(pstack->base);
}

/**
 * 判断一个栈是否为空
 * @param pstack
 * @return
 */
static bool anvei_rpn_stack_empty(const anvei_rpn_stack *pstack)
{
    return pstack->top == pstack->base;
}

/**
 * 将一个元素压入字符串栈
 * @param pstack
 * @param ele
 * @return
 */
static bool anvei_rpn_stack_push(anvei_rpn_stack *pstack, anvei_rpn_string ele)
{
    if (pstack->top - pstack->base == pstack->size)     // 栈的容量已经满了，需要重新分配空间
    {
        anvei_rpn_string *temp = realloc(pstack->base, sizeof(anvei_rpn_string) * (pstack->size + ANVEI_RPN_STACK_INCREMENTSIZE));
        if (!temp) return false;
        pstack->base = temp;
        pstack->top = temp + pstack->size;
        pstack->size += ANVEI_RPN_STACK_INCREMENTSIZE;
    }
    *pstack->top = ele;
    pstack->top++;
    return true;
}

/**
 * 返回栈顶元素
 * @param pstack
 * @return
 */
static anvei_rpn_string anvei_rpn_stack_peek(const anvei_rpn_stack *pstack)
{
    if (anvei_rpn_stack_empty(pstack)) exit(__LINE__);
    return *(pstack->top - 1);
}

/**
 * 返回当前栈顶元素，并将其从栈顶移除
 * @param pstack
 * @return
 */
static anvei_rpn_string anvei_rpn_stack_pop(anvei_rpn_stack *pstack)
{
    if (anvei_rpn_stack_empty(pstack))
        exit(__LINE__);
    pstack->top--;
    return *pstack->top;
}

/**
 * 初始化一个字符串顺序表
 * @param plist
 * @return
 */
static bool anvei_rpn_seqlist_init(anvei_rpn_seqlist *plist)
{
    anvei_rpn_string *pele = malloc(sizeof(anvei_rpn_string) * ANVEI_RPN_SEQLIST_INITSIZE);
    if (!pele) return false;
    plist->length = 0;
    plist->size = ANVEI_RPN_SEQLIST_INITSIZE;
    plist->data = pele;
    return true;
}

/**
 * 销毁一个字符串顺序表
 * @param plist
 */
static void anvei_rpn_seqlist_destory(anvei_rpn_seqlist *plist)
{
    free(plist->data);
}

/**
 * 获取顺序表指定下标元素
 * @param list
 * @param index
 * @return
 */
static anvei_rpn_string  anvei_rpn_seqlist_get(anvei_rpn_seqlist list, int index)
{
    return *(list.data + index);
}

/**
 * 向顺序表指定下标插入一个元素
 * @param plist
 * @param index
 * @param ele
 * @return
 */
static bool anvei_rpn_seqlist_insert(anvei_rpn_seqlist *plist, int index, anvei_rpn_string ele)
{
    if (index > plist->length) return false;
    if (plist->length == plist->size)   // 如果顺序表容量已经满了，需要重新分配内存
    {
        anvei_rpn_string *temp = realloc(plist->data,
                                         sizeof(anvei_rpn_string) * (plist->length + ANVEI_RPN_SEQLIST_INCREMENTSIZE));
        if (!temp) return false;
        plist->size += ANVEI_RPN_SEQLIST_INCREMENTSIZE;
        plist->data = temp;
    }
    for (int i = index; i < plist->length; i++) // 将下标index开始的元素向后移一位
    {
        plist->data[i + 1] = plist->data[i];
    }
    plist->data[index] = ele;
    plist->length++;
    return true;
}

/**
 * 删除顺序表指定下标一个元素
 * @param plist
 * @param index
 */
static void anvei_rpn_seqlist_delete(anvei_rpn_seqlist *plist, int index)
{
    for (int i = index; i < plist->length - 1; i++)     // 前移一位
    {
        plist->data[index] = plist->data[index + 1];
    }
    plist->length--;
}

/**
 * 清空一个顺序表
 * @param plist
 */
static void anvei_rpn_seqlist_clear(anvei_rpn_seqlist *plist)
{
    plist->length = 0;
}

/**
 * 判断一个顺序表是否为空
 * @param list
 * @return
 */
static bool anvei_rpn_seqlist_empty(anvei_rpn_seqlist list)
{
    return list.length == 0;
}

/**
 * 将一个字符串解析成一个double值
 * @param num
 * @return
 */
static double anvei_rpn_parse_double(anvei_rpn_string num)
{
    double res = 0;
    bool dot_flag = false;
    int dot_pos = -1;
    for (int i = 0; i < num.len; i++)       // 确认小数点位置
    {
        char ch = anvei_rpn_str_get(num, i);
        if (ch == '.')
        {
            if (!dot_flag)
            {
                dot_flag = true;
                dot_pos = i;
            }
            else exit(__LINE__);          // 一个数字字符不允许两个小数点
        }
        else if (isdigit(ch))
        {
            continue;
        }
        else                // 非数字字符错误
        {
            exit(__LINE__);
        }
    }
    if (!dot_flag) dot_pos = num.len;
    for (int i = 0; i < dot_pos; i++)
    {
        res += (anvei_rpn_str_get(num, i) - '0') * pow(10, dot_pos - i - 1);
    }
    for (int i = dot_pos + 1; i < num.len; i++)
    {
        res += (anvei_rpn_str_get(num, i) - '0') * pow(10, dot_pos - i);
    }
    return res;
}

/**
 * 将一个double值转为字符串，该字符串记得释放
 * @param num
 * @return
 */
static anvei_rpn_string anvei_rpn_tostring(double num)
{
    anvei_rpn_string res;
    anvei_rpn_str_init_by_size(&res, 7);
    char temp[7] = {0};
    sprintf(temp, "%.4f", num);
    for (int i = 0; i < 7; i++)
    {
        if (temp[i] == '\0') break;
        anvei_rpn_str_set(&res, i, temp[i]);
    }
    return res;
}

/**
 * 判断一个字符串是否是操作符
 * @param token
 * @return
 */
static bool anvei_rpn_is_operator(anvei_rpn_string token)
{
    for (int i = 0; i < 5; i++)
    {
        if (operators[i][0] == anvei_rpn_str_get(token, 0))
            return true;
    }
    return false;
}

/**
 * 判断一个字符串是否时括号
 * @param token
 * @return
 */
static bool anvei_rpn_is_bracket(anvei_rpn_string token)
{
    char ch = anvei_rpn_str_get(token, 0);
    return ch == '(' || ch == ')';
}

/**
 * 判断运算符a优先级是否高于b
 * @param a
 * @param b
 * @return
 */
static bool anvei_rpn_is_priority(char a, char b)
{
    if (a == '+' || a == '-')
    {
        return false;
    }
    else
    {
        if (b == '+' || b == '-') return true;
        return false;
    }
}

/**
 * 中缀表达式转逆波兰式时调用，包含处理操作符的逻辑
 * @param operator
 * @param list
 * @param stack
 */
static void
anvei_rpn_handleOperator(anvei_rpn_string operator, anvei_rpn_seqlist *list, anvei_rpn_stack *stack)
{
    if (anvei_rpn_stack_empty(stack) || anvei_rpn_str_get(anvei_rpn_stack_peek(stack), 0) == '(')
        anvei_rpn_stack_push(stack, operator);
    else if (anvei_rpn_is_priority(anvei_rpn_str_get(operator, 0),
                                   anvei_rpn_str_get(anvei_rpn_stack_peek(stack), 0)))
    {
        anvei_rpn_stack_push(stack, operator);
    }
    else
    {
        anvei_rpn_seqlist_insert(list, list->length, anvei_rpn_stack_pop(stack));
        anvei_rpn_handleOperator(operator, list, stack);
    }
}

/**
 * 中缀表达式转逆波兰式时调用，包含处理括号的逻辑
 * @param bracket
 * @param list
 * @param stack
 */
static void
anvei_rpn_handleBracket(anvei_rpn_string bracket, anvei_rpn_seqlist *list, anvei_rpn_stack *stack)
{
    if (anvei_rpn_str_get(bracket, 0) == '(')
        anvei_rpn_stack_push(stack, bracket);
    else
    {
        while (anvei_rpn_str_get(anvei_rpn_stack_peek(stack), 0) != '(')
            anvei_rpn_seqlist_insert(list, list->length, anvei_rpn_stack_pop(stack));
        anvei_rpn_stack_pop(stack);
    }
}

/**
 * 中缀表达式转逆波兰式时调用，包含处理操作数的逻辑
 * @param num
 * @param list
 */
static void
anvei_rpn_handleNumber(anvei_rpn_string num, anvei_rpn_seqlist *list)
{
    anvei_rpn_seqlist_insert(list, list->length, num);
}

/**
 * 将字符串infix切割成tokens，结果存入infix_list
 * @param infix
 * @param infix_list
 */
static void anvei_rpn_split_infix(const char *infix, anvei_rpn_seqlist *infix_list)
{
    int len = (int) strlen(infix);
    char temp[10] = {0};
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        char ch = *infix++;
        if (i == len - 1 && ch != ')')
        {
            temp[index] = ch;
            anvei_rpn_string str1;
            anvei_rpn_str_init(&str1, temp);
            anvei_rpn_seqlist_insert(infix_list, infix_list->length, str1);
            break;
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')')
        {
            if (index != 0)
            {
                anvei_rpn_string str1;
                anvei_rpn_str_init(&str1, temp);
                anvei_rpn_seqlist_insert(infix_list, infix_list->length, str1);
            }
            anvei_rpn_string str2;
            anvei_rpn_str_init_by_size(&str2, 1);
            anvei_rpn_str_set(&str2, 0, ch);
            anvei_rpn_seqlist_insert(infix_list, infix_list->length, str2);
            for (int j = 0; j < index + 1; j++)
            {
                temp[i] = '\0';
            }
            index = 0;
        }
        else if (isdigit(ch) || ch == '.')
        {
            temp[index++] = ch;
        }
        else if (ch == ' ')
            continue;
        else
            exit(__LINE__);
    }
}

/**
 * 根据顺序表infix_list中的中缀表达式tokens，转成逆波兰式tokens，结果保存在suffix_list
 * @param infix_list
 * @param suffix_list
 */
static void anvei_rpn_infix_to_suffix(anvei_rpn_seqlist *infix_list, anvei_rpn_seqlist *suffix_list)
{
    anvei_rpn_stack op_stack;
    anvei_rpn_stack_init(&op_stack);
    for (int i = 0; i < infix_list->length; i++)
    {
        anvei_rpn_string token = anvei_rpn_seqlist_get(*infix_list, i);
        if (anvei_rpn_is_operator(token))
        {
            anvei_rpn_handleOperator(token, suffix_list, &op_stack);
        }
        else if (anvei_rpn_is_bracket(token))
        {
            anvei_rpn_handleBracket(token, suffix_list, &op_stack);
        }
        else
        {
            anvei_rpn_handleNumber(token, suffix_list);
        }
    }
    while (!anvei_rpn_stack_empty(&op_stack))
    {
        anvei_rpn_seqlist_insert(suffix_list, suffix_list->length, anvei_rpn_stack_pop(&op_stack));
    }
    anvei_rpn_stack_destory(&op_stack);
}

/**
 * 计算逆波兰式
 * @param suffix_list
 * @return
 */
static double anvei_rpn_calc_suffix_expression(anvei_rpn_seqlist suffix_list)
{
    anvei_rpn_stack res_stack;
    anvei_rpn_seqlist temp_list;
    anvei_rpn_stack_init(&res_stack);
    anvei_rpn_seqlist_init(&temp_list);         // 用于保存该函数内部先创建的字符串，以便释放其内存
    for (int i = 0; i < suffix_list.length; i++)
    {
        anvei_rpn_string token = anvei_rpn_seqlist_get(suffix_list, i);
        if (anvei_rpn_is_operator(token))   // 处理操作符
        {
            double operand1 = anvei_rpn_parse_double(anvei_rpn_stack_pop(&res_stack));
            double operand2 = anvei_rpn_parse_double(anvei_rpn_stack_pop(&res_stack));
            double calc_res = 0;
            switch (*token.str) {
                case '+':
                    calc_res = operand2 + operand1;
                    break;
                case '-':
                    calc_res = operand2 - operand1;
                    break;
                case '*':
                    calc_res = operand2 * operand1;
                    break;
                case '/':
                    calc_res = operand2 / operand1;
                    break;
                case '^':
                    calc_res = pow(operand2, operand1);
                    break;
                default:
                    break;
            }
            anvei_rpn_string temp = anvei_rpn_tostring(calc_res);
            anvei_rpn_stack_push(&res_stack, temp);
            anvei_rpn_seqlist_insert(&temp_list, temp_list.length, temp);
        }
        else                                // 处理操作数
        {
            anvei_rpn_stack_push(&res_stack, token);
        }
    }
    double res = anvei_rpn_parse_double(anvei_rpn_stack_pop(&res_stack));
    // 清理堆内存
    for (int i = 0; i < temp_list.length; i++)
    {
        anvei_rpn_str_destory(anvei_rpn_seqlist_get(temp_list, i));
    }
    anvei_rpn_stack_destory(&res_stack);
    anvei_rpn_seqlist_destory(&temp_list);
    return res;
}

/**
 * 根据给定的字符串表达式计算其值
 * @param infix
 * @return
 */
double anvei_rpn_get_result(const char *infix)
{
    anvei_rpn_seqlist infix_list, suffix_list;
    anvei_rpn_seqlist_init(&infix_list);
    anvei_rpn_seqlist_init(&suffix_list);

    anvei_rpn_split_infix(infix, &infix_list);       // 切割infix，结果保存在infix_list中
    anvei_rpn_infix_to_suffix(&infix_list, &suffix_list);     // 中缀表达式转逆波兰式
    double res = anvei_rpn_calc_suffix_expression(suffix_list);          // 计算逆波兰式的值

    for (int i = 0; i < infix_list.length; i++)
    {
        anvei_rpn_str_destory(anvei_rpn_seqlist_get(infix_list, i));
    }
    anvei_rpn_seqlist_destory(&infix_list);
    anvei_rpn_seqlist_destory(&suffix_list);

    return res;
}

int main(void)
{
    const char *expression = "1 + 2 * 6 ^ 3";
    double value = anvei_rpn_get_result(expression);
    printf("value = %f\n", value);

    return 0;
}