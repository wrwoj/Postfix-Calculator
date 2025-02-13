#include "input_output.h"



int checkPrecidenceLevel(char op) {
    switch (op) {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case 'F':
    case 'N':
    case 'X':
        return 3;
    case 'T':
        return 5;
    default:
        return -1;
    }
}

bool checkPrecidence(char a, char b) {
    return checkPrecidenceLevel(a) >= checkPrecidenceLevel(b);
}

void handle_input(stack<char>& charstack, queue<int>& intqueue, queue<char>& postfix, queue<int>& arguments) {
    int number = 0;
    bool number_is_empty = true;
    int argcount = 0;
    char a;
    char b;
    char prev = 'O';
    int n = 0;
    stack<int> arg_stack;
    while (std::cin.get(a)) {
        if (a < '0' || a> '9') {
            if (!number_is_empty) {
                intqueue.push(number);
                postfix.push('n');
                number = 0;
                number_is_empty = true;
            }
            if (a == '(') {
                arg_stack.push(1);
                charstack.push(a);
            }
            if (a == '+' || a == '-' || a == '*' || a == '/') {
                while (charstack.head != nullptr && charstack.head->val != '(' && checkPrecidence(charstack.head->val, a)) {
                    b = charstack.pop();
                    postfix.push(b);
                }
                charstack.push(a);
            }
            if (a == 'F' || (a == 'N' && prev == 'I') || a == 'X') {
                charstack.push(a);
            }
            if (a == 'N' && prev != 'I') {
                charstack.push('T');
                postfix.push('|');
            }
            else if (postfix.head != nullptr && charstack.head != nullptr && charstack.head->val == 'T' && postfix.head->val == 'n') {
                b = charstack.pop();
                postfix.push(b);
            }
            if (a == ')') {
                argcount = arg_stack.pop();
                b = charstack.pop();
                while (b != '(') {
                    postfix.push(b);
                    b = charstack.pop();
                }
                if (charstack.head != nullptr && (charstack.head->val == 'N' || charstack.head->val == 'X')) {
                    b = charstack.pop();
                    postfix.push(b);
                    arguments.push(argcount);
                }
                if (charstack.head != nullptr && charstack.head->val == 'F') {
                    b = charstack.pop();
                    postfix.push(b);
                }
            }
            if (a == '.') {
                while (charstack.head != nullptr) {
                    b = charstack.pop();
                    postfix.push(b);
                }
                break;
            }
            if (a == ',') {
                b = charstack.pop();
                while (b != '(') {
                    postfix.push(b);
                    b = charstack.pop();
                }
                charstack.push('(');
                n = arg_stack.pop();
                n++;
                arg_stack.push(n);
            }


        }
        else {
            number *= 10;
            number += a - '0';
            number_is_empty = false;
        }
        prev = a;
    }
    if (!number_is_empty) {
        intqueue.push(number);
        postfix.push('n');
        number = 0;
        number_is_empty = true;
    }
}


void printpostfix(queue<int> intc, queue<char> charc, queue<int> argc) {
    queue<int>intqueue;
    queue<char>postfix;
    queue<int>arguments;
    intqueue = intc;
    postfix = charc;
    arguments = argc;
    while (postfix.tail != nullptr) {
        char a = postfix.pop();
        switch (a) {
        case '|':
            break;
        case 'F':
            std::cout << "IF ";
            break;
        case 'X':
            std::cout << "MAX" << arguments.pop() << " ";
            break;
        case 'N':
            std::cout << "MIN" << arguments.pop() << " ";
            break;
        case 'T':
            std::cout << "N" << " ";
            break;
        case 'n':
            std::cout << intqueue.pop() << " ";
            break;
        default:
            std::cout << a << " ";
            break;
        }
    }
    std::cout << std::endl;
}

