//
// Created by Anvei on 2022/10/11.
//

#include "ds/rpn_datastructure.h"
#include "../../utils/errorutils.h"
#include "strutils.h"
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>


/**
 * 将一个字符串解析成一个double值
 * @param num
 * @return
 */
inline static double rpn_parse_double(const String num)
{
    return parse_double(num.str);
}

/**
 * 将一个double值转为字符串，该字符串记得释放
 * @param num
 * @return
 */
static String rpn_tostring(double num)
{
    String res;
    str_init_by_size(&res, 10);
    char temp[16] = {0};
    sprintf(temp, "%.4f", num);
    for (int i = 0; i < 16; i++)
    {
        if (temp[i] == '\0') break;
        str_set(&res, i, temp[i]);
    }
    return res;
}

/**
 * 判断一个字符串是否是操作符
 * @param token
 * @return
 */
inline static bool rpn_is_operator(String token)
{
    switch(*token.str)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;
        default:
            return false;
    }
}

/**
 * 判断一个字符串是否时括号
 * @param token
 * @return
 */
inline static bool rpn_is_bracket(String token)
{
    switch (*token.str) {
        case '(':
        case ')':
            return true;
        default:
            return false;
    }
}

/**
 * 判断运算符a优先级是否高于b
 * @param a
 * @param b
 * @return
 */
static bool rpn_is_priority(char a, char b)
{
    switch (a) {
        case '+':
        case '-':
            return false;           // 如果a是+或-，直接返回false
        case '*':
        case '/':
        case '^':
            if (b == '+' || b == '-')
                return true;
            return false;
        default:
            return false;
    }
}

/**
 * 中缀表达式转逆波兰式时调用，包含处理操作符的逻辑
 * @param operator
 * @param plist
 * @param pstack
 */
static void rpn_handleOperator
(const String operator, rpn_seqlist *plist, rpn_stack *pstack)
{
    // 如果栈为空，或者栈顶为 "("，直接入栈
    if (rpn_stack_empty(pstack) || str_get(rpn_stack_peek(pstack), 0) == '(')
        rpn_stack_push(pstack, operator);
    // 如果该操作符优先级高于当前栈顶元素，也是直接入栈
    else if (rpn_is_priority(str_get(operator, 0),
                                   str_get(rpn_stack_peek(pstack), 0)))
        rpn_stack_push(pstack, operator);
    // 否则，就从栈中弹出一个元素，将其加入逆波兰式列表中，并且通过递归调用函数继续处理该操作符
    else
    {
        rpn_seqlist_add(plist, rpn_stack_pop(pstack));
        rpn_handleOperator(operator, plist, pstack);
    }
}

/**
 * 中缀表达式转逆波兰式时调用，包含处理括号的逻辑
 * @param bracket
 * @param plist
 * @param pstack
 */
static void rpn_handleBracket
(const String bracket, rpn_seqlist *plist, rpn_stack *pstack)
{
    if (str_get(bracket, 0) == '(')
        rpn_stack_push(pstack, bracket);
    else
    {
        while (str_get(rpn_stack_peek(pstack), 0) != '(')
            rpn_seqlist_add(plist, rpn_stack_pop(pstack));
        rpn_stack_pop(pstack);
    }
}

/**
 * 中缀表达式转逆波兰式时调用，包含处理操作数的逻辑
 * @param num
 * @param plist
 */
inline static void rpn_handleNumber
(const String num, rpn_seqlist *plist)
{
    rpn_seqlist_add(plist, num);
}

/**
 * 将字符串infix切割成tokens，结果存入infix_list,记得最后要释放该列表中保存的字符串类型变量的内存
 * @param infix
 * @param pinfix_list
 */
static void rpn_split_infix(const char *infix, rpn_seqlist *pinfix_list)
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
            String str1;
            str_init(&str1, temp);
            rpn_seqlist_add(pinfix_list, str1);
            break;
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')')
        {
            if (index != 0)
            {
                String str1;
                str_init(&str1, temp);
                rpn_seqlist_add(pinfix_list, str1);
            }
            String str2;
            str_init_by_size(&str2, 1);
            str_set(&str2, 0, ch);
            rpn_seqlist_add(pinfix_list, str2);
            for (int j = 0; j < index + 1; j++)
            {
                temp[j] = '\0';
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
            anv_error("该字符串存在非法字符!");
    }
}

/**
 * 根据顺序表infix_list中的中缀表达式tokens，转成逆波兰式tokens，结果保存在suffix_list
 * @param pinfix_list
 * @param psuffix_list
 */
static void rpn_infix_to_suffix(rpn_seqlist *pinfix_list, rpn_seqlist *psuffix_list)
{
    rpn_stack op_stack;         // 中间栈，用来存储操作符和括号
    rpn_stack_init(&op_stack);
    for (int i = 0; i < pinfix_list->length; i++)
    {
        String token = rpn_seqlist_get(*pinfix_list, i);
        if (rpn_is_operator(token))
        {
            rpn_handleOperator(token, psuffix_list, &op_stack);
        }
        else if (rpn_is_bracket(token))
        {
            rpn_handleBracket(token, psuffix_list, &op_stack);
        }
        else
        {
            rpn_handleNumber(token, psuffix_list);
        }
    }
    // 将栈中剩余操作符全部添加进逆波兰式列表中
    while (!rpn_stack_empty(&op_stack))
    {
        rpn_seqlist_add(psuffix_list, rpn_stack_pop(&op_stack));
    }
    // 只需要销毁栈即可，因为该函数内部没有创建字符串类型变量
    rpn_stack_destory(&op_stack);
}

/**
 * 计算逆波兰式
 * @param suffix_list
 * @return
 */
static double rpn_calc_suffix_expression(rpn_seqlist suffix_list)
{
    rpn_stack res_stack;
    rpn_seqlist heap_memory_collector;
    rpn_stack_init(&res_stack);
    rpn_seqlist_init(&heap_memory_collector);         // 用于保存该函数内创建的堆内存上的字符串，以便释放其内存
    for (int i = 0; i < suffix_list.length; i++)
    {
        String token = rpn_seqlist_get(suffix_list, i);
        if (rpn_is_operator(token))   // 处理操作符
        {
            double operand1 = rpn_parse_double(rpn_stack_pop(&res_stack));
            double operand2 = rpn_parse_double(rpn_stack_pop(&res_stack));
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
            String temp = rpn_tostring(calc_res);
            rpn_stack_push(&res_stack, temp);        // 遇见操作符，就从栈中弹出两个操作数，计算完成后，将结果压入栈中
            rpn_seqlist_add(&heap_memory_collector, temp);
        }
        else  // 遇见操作数，直接入栈
        {
            rpn_stack_push(&res_stack, token);
        }
    }
    double res = rpn_parse_double(rpn_stack_pop(&res_stack));
    // 清理堆内存
    for (int i = 0; i < heap_memory_collector.length; i++)
    {
        str_destory(rpn_seqlist_get(heap_memory_collector, i));
    }
    rpn_stack_destory(&res_stack);
    rpn_seqlist_destory(&heap_memory_collector);
    return res;
}

/**
 * 根据给定的字符串表达式计算其值
 * @param infix
 * @return
 */
double rpn_eval(const char *infix)
{
    rpn_seqlist infix_list, suffix_list;
    rpn_seqlist_init(&infix_list);
    rpn_seqlist_init(&suffix_list);

    // 切割infix，结果保存在infix_list中
    rpn_split_infix(infix, &infix_list);
    printf("中缀表达式: \n");
    for (int i = 0; i < infix_list.length; i++)
    {
        str_putstring(rpn_seqlist_get(infix_list, i));
        putchar(' ');
    }
    printf("\n");

    // 中缀表达式转逆波兰式
    rpn_infix_to_suffix(&infix_list, &suffix_list);
    printf("逆波兰式: \n");
    for (int i = 0; i < suffix_list.length; i++)
    {
        str_putstring(rpn_seqlist_get(suffix_list, i));
        putchar(' ');
    }
    printf("\n");

    // 计算逆波兰式的值
    double res = rpn_calc_suffix_expression(suffix_list);

    // 清理堆内存
    for (int i = 0; i < infix_list.length; i++)
    {
        str_destory(rpn_seqlist_get(infix_list, i));
    }

    rpn_seqlist_destory(&infix_list);
    rpn_seqlist_destory(&suffix_list);

    return res;
}
