//
// Created by Anvei on 2022/10/12.
//

#ifndef ALGORITHM_ERRORUTILS_H
#define ALGORITHM_ERRORUTILS_H
#undef NDEBUG
#ifdef __cplusplus
extern "C" {
#endif

void anv_tracing_format(const char *file, const char *func, unsigned line, const char *mesg, int level);
void anv_tracing_assert(const char *expression, const char *file, const char *func, unsigned line);

#ifdef __cplusplus
}
#endif

#define ANV_DEBUG 1
#define ANV_ERROR 2

#define anv_error(s) anv_tracing_format(__FILE__, __func__, __LINE__, s, ANV_ERROR)
#define anv_debug(s) anv_tracing_format(__FILE__, __func__, __LINE__, s, ANV_DEBUG)

#undef anv_assert
#ifdef NDEBUG
#define anv_assert(expression) ((void) 0)
#else
#define ANV_STR(x) #x
#define anv_assert(expression) ((expression) ? (void) 0 : \
    anv_tracing_assert(ANV_STR(expression), __FILE__, __func__, __LINE__))

#endif

#endif //ALGORITHM_ERRORUTILS_H
