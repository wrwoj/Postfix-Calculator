#include "calculations.h"

void divide(stack<int>& intstack) {
    int d, b;
    std::cout << "/ ";
    intstack.print();
    d = intstack.pop();
    b = intstack.pop();
    if (d == 0) {
        throw(1);
        return;
    }
    d = b / d;
    intstack.push(d);
    return;
}

void add(stack<int>& intstack) {
    int d, b;
    std::cout << "+ ";
    intstack.print();
    d = intstack.pop();
    b = intstack.pop();
    d = b + d;
    intstack.push(d);
}

void subtract(stack<int>& intstack) {
    int d, b;
    std::cout << "- ";
    intstack.print();
    d = intstack.pop();
    b = intstack.pop();
    d = b - d;
    intstack.push(d);
}

void multiply(stack<int>& intstack) {
    int d, b;
    std::cout << "* ";
    intstack.print();
    d = intstack.pop();
    b = intstack.pop();
    d = b * d;
    intstack.push(d);
}

void iffunc(stack<int>& intstack) {
    int d, b, n;
    std::cout << "IF ";
    intstack.print();
    d = intstack.pop();
    b = intstack.pop();
    n = intstack.pop();
    if (n > 0) {
        intstack.push(b);
    }
    else {
        intstack.push(d);
    }
}

void min(stack<int>& intstack, queue<int>& arguments) {
    int b, n, best;
    b = arguments.pop();
    std::cout << "MIN" << b << " ";
    intstack.print();
    best = intstack.pop();
    for (int i = 0; i < b - 1; i++) {
        n = intstack.pop();
        if (n < best) {
            best = n;
        }
    }
    intstack.push(best);
}

void max(stack<int>& intstack, queue<int>& arguments) {
    int b, n, best;
    b = arguments.pop();
    std::cout << "MAX" << b << " ";
    intstack.print();
    best = intstack.pop();
    for (int i = 0; i < b - 1; i++) {
        n = intstack.pop();
        if (n > best) {
            best = n;
        }
    }
    intstack.push(best);
}

void neg(stack<int>& intstack) {
    int d;
    std::cout << "N" << " ";
    intstack.print();
    d = intstack.pop();
    d = -d;
    intstack.push(d);
}


void perform_calculations(queue<int> intqueue, queue<char> postfix, queue<int> arguments) {
    stack<int> intstack;
    int b;
    while (postfix.tail != nullptr) {
        int* arr = nullptr;
        char a = postfix.pop();
        switch (a) {
        case '|':
            break;
        case '+':
            add(intstack);
            break;
        case '-':
            subtract(intstack);
            break;
        case '*':
            multiply(intstack);
            break;
        case '/':
            try {
                divide(intstack);
            }
            catch (...) {
                std::cout << "ERROR" << std::endl << std::endl;
                return;
            }
            break;
        case 'F':
            iffunc(intstack);
            break;
        case 'X':
            max(intstack, arguments);
            break;
        case 'N':
            min(intstack, arguments);
            break;
        case 'T':
            neg(intstack);
            break;
        case 'n':
            b = intqueue.pop();
            intstack.push(b);
            break;
        default:
            std::cout << a << " ";
            break;
        }
        delete[] arr;
    }
    intstack.print();
    std::cout << std::endl;
}
