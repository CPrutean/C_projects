#ifndef OPERATION_H
#define OPERATION_H
typedef struct oper {
    float num1;
    float num2;
    char oper;
} operation;

typedef struct oper_tr {
    operation* left;
    operation* right;
    float num_left;
    float num_right;
    char oper;
} operation_tree;
#endif
