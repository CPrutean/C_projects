#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "operation.h"

#define bool int
#define true 1
#define false 0




//Initialize character array with the index's showing the precedences each operation by index
const char val_symb[9] = {'(',')','^','x','*','/','+','-','.'};
const char val_nums[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
static char* raw_string = NULL;
static int length = 0;


//Pass an operation with only num1 value set and the operator as '!'
float factorial(operation op) {
    bool check_whole_num = true;
    if ((int)op.num1-op.num1 != 0) {
        printf("\nDont pass decimal numbers to the factorial function there is no framework for integrals yet");
        exit(0);
    }

    if (op.oper != '!') {
        printf("\nInvalid operation passed to factorial func");
        return -1;
    }
    
    int i;
    int num = op.num1;
    for (i = op.num1-1; i > 0; i--) {
        num *= i;
    }
    return num;
}

float exponent(operation op) {
    if (op.oper != '^') {
        printf("\nInvalid operation passed to exp function");
        return -1;
    }

    if ((int)op.num2 - op.num2 != 0) {
        printf("\nDont pass non integers into the second argument calculator is incomplete.");
    }

    int i;
    int num = op.num1;
    for (i = 0; i < op.num2; i++) {
        num *= op.num1;
    }
    return num;
}

float paren_parser(char* string, int index1, int index2) {

}


bool is_oper(char c) {
    return (int)c == 42 || (int)c == 43 || (int)c == 47 || (int)c == 94 || (int)c == 120 || (int)c == 47 || (int)c == 45 || (int)c == 46;
}

bool is_num(char c) {
    if ((int) c >= 49 && (int) c <= 57) {
        return true;
    } else {
        return false;
    }
}

bool check_errors(char* string) {
    int i = 0;
    int open_paren = 0;
    int closed_paren = 0;
    int currspaces = 0;
    bool reading_num = false;
    bool decimal_point = false;

    while (*(string+i) != '\0') {
        if (*(string+i) == ' ') {
            decimal_point = false;
            reading_num = false;
            currspaces++;
            continue;
        }

        if (*(string+i) == '(') {
            open_paren++;
        } else if (*(string+i) == ')') {
            closed_paren++;
        } else if (is_num(*(string+i)) && !reading_num) {
            reading_num = true;
        } else if (reading_num && *(string+i) == '.') {
            decimal_point = true;
        } else if (reading_num && decimal_point && (*(string+i) == '.')) {
            printf("\n Improper decimal point usage try again");
            exit(0);
        } else if (i != 0 && is_oper(*(string+i-1)) && is_oper(*(string+i))) {
            printf("\nImproper operation placement try again");
            exit(0);
        } else if (is_oper(*(string+i))) {
            reading_num = false;
            decimal_point = false;
        } else {
            printf("\nThis character '%c' isnt allowed in equations try again", *(string+i));
            exit(0);
        }
        i++;
    }

    if (open_paren != closed_paren) {
        printf("\n Unclosed/Too many open parentheses please try again");
        return false;
    }
    length = i;
    return true;

}

int num_from_char(char c) {
    switch (c) {
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7': 
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case '0':
            return 0;
    }
}

float num_parser(char* string, int index1, int index2, int decimal_index) {
    int i = index1;
    float number = 0;
    int currmult = 1;
    if (decimal_index != -1) {
        int ind1 = decimal_index-1;
        int ind2 = decimal_index+1;
        while (ind1!=index1||ind2!=index2) {
            if (ind1!=index1) {
                number += num_from_char(*(string+i))*currmult;
                ind1--;
            }

            if (ind2!=index2) {
                number += (double)num_from_char(*(string+i))/currmult;
                ind2++;
            }
            currmult *= 10;
        }
        return number;
    } else {
        int i;
        for (i = index2; i >= index1; i--) {
            number += num_from_char(*(string+i))*currmult;
            currmult*=10;
        }
        return number;
    }
}


operation_tree eq_parser(char* string) {
    bool reading_num = false;
    int index1 = 0;
    int index2 = 0;
    char curr_oper;
    //Decimal index will be initialized to -1 if a decimal point doesnt exist
    int decimal_index = -1;
    int i;
    for (i = 0; i <= length; i++) {
        if (reading_num = false && is_num(*(string+i))) {
            reading_num = true;
            index1 = i;
        } else if (reading_num = true && *(string+i) == '.') {
            decimal_index = i;
        } else if (is_oper(*(string+i))) {
            curr_oper = *(string+i);
        }  
    }
}


int main() {
    printf("Enter a valid equation, operators include [ (, ), ^, x, *, /, +, - ]: \n");
    printf("\nNote numbers with commas will result in an error");
    int i;
    
    raw_string = malloc(sizeof(char)*200);
    scanf("%199s", raw_string);

    if (check_errors(raw_string)) {
        printf("\nNo errors found");
    }

    
    return 0;       
}