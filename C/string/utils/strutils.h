//
// Created by Anvei on 2022/10/8.
//

#ifndef ALGORITHM_STRUTILS_H
#define ALGORITHM_STRUTILS_H
#ifdef __cplusplus
extern "C" {
#endif

int kmp_match(const char *target, const char *pattern, int pos);

int brute_force_match(const char *target, const char *pattern, int pos);

double rpn_eval(const char *infix);

double parse_double(const char *expr);

#ifdef __cplusplus
}
#endif
#endif //ALGORITHM_STRUTILS_H
