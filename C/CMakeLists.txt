cmake_minimum_required(VERSION 3.19)
project(Algorithm C)

set(CMAKE_C_STANDARD 11)

add_library(Algorithm library.c library.h
        # 数据结构
        dataStructure/SequenceList.c dataStructure/SequenceList.h
        dataStructure/LinkedList.c dataStructure/LinkedList.h
        dataStructure/Stack.c dataStructure/Stack.h
        # 排序算法
        sort/sortutils.c sort/sortutils.h
        sort/basic_sort.c sort/sort.h
        # 字符串工具
        string/util/pattern_match.c string/util/strutils.h)


# 测试顺序表
add_executable(example_seqlist dataStructure/examples/seqlist/base.c
        dataStructure/SequenceList.h dataStructure/SequenceList.c)

# 测试栈
add_executable(example_stack dataStructure/examples/stack/base.c
        dataStructure/Stack.h dataStructure/Stack.c)

# 测试realloc()函数
add_executable(test_realloc dataStructure/examples/realloc/base.c)

# 测试链表
add_executable(example_lklist dataStructure/examples/lklist/base.c
        dataStructure/LinkedList.h dataStructure/LinkedList.c)

# 测试字符串模式匹配
add_executable(test_string_match string/util/strutils.h string/util/pattern_match.c
        string/test/test_pattern_macth.c)

# 测试基本排序算法
add_executable(test_basic_sort sort/sort.h sort/sortutils.h
        sort/test/test_basic_sort.c)