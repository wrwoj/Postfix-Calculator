// The handle_input function processes input of an infix mathematical equation character by character and converts it to a postfix expression
//  using a commonly known stack algorithm.  It's important to note that for efficiency, numbers are not stored directly in the postfix queue. 
// Instead, they are stored in an intqueue, while the postfix queue only stores operator characters ('n'). During the calculation of the postfix 
// expression, when encountering a 'n' character, the corresponding value is simply popped from the intqueue. 
// It's worth noting that this solution may not be the most memory-efficient if numbers are smaller than 10000.
// Additionally, when encountering functions such as 'MIN', 'MAX', 'IF', etc., only one letter corresponding to them is stored: 
// 'MAX' -> 'X', 'MIN' -> 'N', 'IF' -> 'F', 'N'->'T. 
// Additionally, the arguments queue and stack are utilized to calculate and store the arguments for MIN/MAX functions.

// The checkPrecedenceLevel function checks the precedence property of a given mathematical operation corresponding to the provided character.

// The checkPrecedence function determines whether the precedence level of operation 'a' is greater than or equal to the precedence level of operation 'b'.

// The printpostfix is a simple function to print out the postfix queue as if it contained the exact numbers and complete function names.


#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "structs.h" 

int checkPrecidenceLevel(char op);
bool checkPrecidence(char a, char b);
void handle_input(stack<char>& charstack, queue<int>& intqueue, queue<char>& postfix, queue<int>& arguments);
void printpostfix(queue<int> intc, queue<char> charc, queue<int> argc);

#endif // INPUT_OUTPUT_H
