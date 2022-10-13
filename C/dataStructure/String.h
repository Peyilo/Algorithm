//
// Created by Anvei on 2022/10/9.
//
// 提供了字符串的实现

#ifndef ALGORITHM_STRING_H
#define ALGORITHM_STRING_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct {
    char *str;
    int len;
    int size;
} String;

bool str_init(String *pstr, const char *init_str);

bool str_init_by_size(String *pstr, int len);

void str_destory(String str);

String str_add(String a, String b);

bool str_set(String *pstr, int index, char ch);

char str_get(String str, int index);

void str_putstring(String str);

#ifdef __cplusplus
}
#endif
#endif //ALGORITHM_STRING_H
