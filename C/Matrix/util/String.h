//
// Created by Anvei on 2022/9/24.
//

#ifndef MATRIX_STRING_H
#define MATRIX_STRING_H

typedef struct {
    char * str;
    int len;
} String;

String * initString(char *str, int len);

void destroyString(String *pString);

void printString(String string);

#endif //MATRIX_STRING_H
