#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "structs.h" 

//  These functions evaluate  postfix expression as stored in given queue.

void divide(stack<int>& intstack);
void add(stack<int>& intstack);
void subtract(stack<int>& intstack);
void multiply(stack<int>& intstack);
void iffunc(stack<int>& intstack);
void min(stack<int>& intstack, queue<int>& arguments);
void max(stack<int>& intstack, queue<int>& arguments);
void neg(stack<int>& intstack);
void perform_calculations(queue<int> intqueue, queue<char> postfix, queue<int> arguments);

#endif // CALCULATIONS_H
