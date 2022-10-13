cmake_minimum_required(VERSION 3.19)
project(Algorithm C)

set(CMAKE_C_STANDARD 11)

# 数据结构
add_library(Algorithm library.c library.h
        ## 顺序表---元素类型为int
        dataStructure/SequenceList.c dataStructure/SequenceList.h
        ## 链表---元素类型为int
        dataStructure/LinkedList.c dataStructure/LinkedList.h
        ## 顺序栈---元素类型为int
        dataStructure/Stack.c dataStructure/Stack.h
        ## 分数---分子分母采用int类型
        dataStructure/Fraction.c dataStructure/Fraction.h
        ## 矩阵---元素类型为Fraction分数
        dataStructure/Matrix.c dataStructure/Matrix.h
        ## 可变字符串
        dataStructure/String.c dataStructure/String.h
        ## 链队列
        dataStructure/LinkedQueue.c dataStructure/LinkedQueue.h
        ## 循环队列
        dataStructure/CircularQueue.c dataStructure/CircularQueue.h
        ## 排序算法
        sort/sortutils.c sort/sortutils.h
        sort/basic_sort.c sort/sort.h
        ## 工具库
        string/utils/pattern_match.c string/utils/strutils.h string/utils/strutils.c
        number/digitalutils.c number/digitalutils.h string/utils/rpn_expression.c
        string/utils/ds/rpn_datastructure.c string/utils/ds/rpn_datastructure.h
        utils/errorutils.c utils/errorutils.h dataStructure/BSTree.c dataStructure/BSTree.h)

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
add_executable(test_string_match string/utils/strutils.h string/utils/pattern_match.c
        string/test/test_pattern_macth.c)

# 测试基本排序算法
add_executable(test_basic_sort sort/sort.h sort/sortutils.h
        sort/test/test_basic_sort.c)

# 测试RPN算法
add_executable(test_rpn string/test/test_rpn.c
        string/utils/rpn_expression.c string/utils/strutils.h string/utils/strutils.c
        dataStructure/String.c dataStructure/String.h
        string/utils/ds/rpn_datastructure.c string/utils/ds/rpn_datastructure.h
        utils/errorutils.c utils/errorutils.h)

# 测试字符串
add_executable(example_string dataStructure/examples/string/basic.c
        dataStructure/String.c dataStructure/String.h)

# 测试循环队列
add_executable(example_cirqueue dataStructure dataStructure/CircularQueue.c
        dataStructure/CircularQueue.h dataStructure/examples/cirqueue/base.c)

# 测试parse_double()函数
add_executable(test_parse_double string/test/test_parse_double.c
        string/utils/strutils.c string/utils/strutils.h
        utils/errorutils.c utils/errorutils.h)

# 测试errorutils宏
add_executable(test_errorutils utils/test/test_errorutils.c
        utils/errorutils.h utils/errorutils.c)


add_executable(example_BSTree dataStructure/BSTree.c dataStructure/BSTree.h
        utils/errorutils.h utils/errorutils.c dataStructure/examples/BSTree/basic.c)
