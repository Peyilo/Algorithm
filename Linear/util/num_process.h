//
// Created by Anvei on 2022/10/1.
//

#ifndef LINEARALGEBRA_NUM_PROCESS_H
#define LINEARALGEBRA_NUM_PROCESS_H
#include <vector>
using std::vector;

bool isPrime(int num);

int gcd(int num1, int num2);
int gcd(int len, int *list);
int gcd(vector<int> vec);

int lcm(int num1, int num2);
int lcm(int len, int *list);
int lcm(vector<int> vec);

#endif //LINEARALGEBRA_NUM_PROCESS_H
