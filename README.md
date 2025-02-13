# Algorithms and Data Structures projects for my university course
This repository originally contained only the Postfix Calculator program. However, I later decided to add two other tasks that I created during my Algorithms & Data Structures (A&DS) course a year ago, that were too small to publish on their own. In addition to the Postfix Calculator, which is described in more detail below, the repository now also includes a Hex Game implementation and a program for processing graphs and performing various graph analyses.
## Postfix Calculator

### Overview
This project is a component of my Algorithms and Data Structures University course. It implements an integer calculator using postfix notation, also known as reverse Polish notation, to manage operator precedence, functions, and parentheses efficiently. The calculator encompasses various operations such as addition, subtraction, multiplication, division, conditional statements, unary negation, and functions like MIN and MAX. It employs my custom implementations of queue and stack data structures.
### Input
- Number of formulas (`n`)
- `n` formulas, each in infix notation and ending with a dot ('.'). Each token is separated by whitespace characters.
- Operands are positive integers.
- Operators are single characters.
- Functions consist of capital letters.

### Operations Available
1. Addition (+) and Subtraction (-)
2. Multiplication (*) and Division (/) - Division results are rounded down.
3. IF(a, b, c) - Conditional statement.
4. N a - Unary negation.
5. MIN(a1, a2, ...) and MAX(a1, a2, ...) - Functions with variable number of parameters.
6. Parentheses ( ... )

### Output
- The formula in postfix notation.
- Before executing each operation, print the operator/function and the content of the stack.
- The final result.
- Print "ERROR" if encountering division by 0.

### Example
(This example was provided by my professor)
#### Input:

<small>4 \
MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) . \
2 + MIN ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3 .\
N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .\
IF ( ( 6 + 8 ) , ( 4 / 2 ) , MIN ( 8 , 2 , 1 , 0 , 3 ) ) * 2 * 6 / N ( 3 ) .</small>

#### Output:

<small>100  1  34  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6 \
MAX3 2 34 1 100 \
MIN4 77 35 36 66 80 34 100\
MIN6 60 50 35 80 34 100\
34</small>

<small>2  100  1  6  5  *  2  +  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6  3  *  +\
\* 5 6 1 100 2\
\+ 2 30 1 100 2\
MAX3 2 32 1 100 2\
MIN4 77 35 36 66 80 32 100 2\
MIN6 60 50 35 80 32 100 2\
\* 3 32 2\
\+ 96 2\
98\
\
400  N  11  3  2  *  -  2  /  +  200  N  N  +\
N 400\
\* 2 3 11 -400\
\- 6 11 -400\
/ 2 5 -400\
\+ 2 -400\
N 200 -398\
N -200 -398\
\+ 200 -398\
-198\
\
6  8  +  4  2  /  8  2  1  0  3  MIN5  IF  2  *  6  *  3  N  / \
\+ 8 6 \
/ 2 4 14 \
MIN5 3 0 1 2 8 2 14 \
IF 0 2 14 \
\* 2 2\
\* 6 4 \
N 3 24 \
/ -3 24 \
-8</small>
