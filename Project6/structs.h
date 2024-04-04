#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>

// Both stack and queue are essentially lists. The loading process is the same in both of them. 
// The main, if not only, difference between them is the popping process - 
// in a stack, it follows the LIFO rule, while in a queue, it follows the FIFO rule.
// The queue struct also includes an operator=, which the stack struct lacks, as it would be redundant.


template <typename T>
struct node {
    T val = 0;
    node<T>* point = nullptr;
};

template <typename T>
struct stack {
    node<T>* head = nullptr;
    node<T>* tail = nullptr;

    void push(const T& value);
    ~stack();
    T pop();
    void print();
};

template <typename T>
struct queue {
    node<T>* head = nullptr;
    node<T>* tail = nullptr;

    void push(const T& value);
    T pop();
    void print();
    queue& operator=(const queue& other);
};

#endif //STRUCTS_H
