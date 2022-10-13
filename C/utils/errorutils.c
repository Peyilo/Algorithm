//
// Created by Anvei on 2022/10/12.
//

#include "errorutils.h"
#include <stdlib.h>
#include <stdio.h>

void anv_tracing_format(const char * file, const char *func, unsigned line, const char *mesg, int level)
{
    switch (level) {
        case ANV_DEBUG:
            fprintf(stderr, "%s:%d [%s] debug: %s\n", file, line, func, mesg);
            break;
        case ANV_ERROR:
            fprintf(stderr, "%s:%d [%s] error: %s\n", file, line, func, mesg);
            exit(-1);
        default:
            break;
    }
}

_Noreturn void anv_tracing_assert(const char *expression, const char *file, const char *func, unsigned line)
{
    fprintf(stderr, "%s:%d [%s] assertion failed: %s\n", file, line, func, expression);
    abort();
}