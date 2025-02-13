#include <iostream>
#include "calculations.h"
#include "input_output.h"


int main()
{
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        stack<char> charstack;
        queue<int> intqueue;
        queue<char> postfix;
        queue<int> arguments;
        handle_input(charstack, intqueue, postfix, arguments);
        printpostfix(intqueue, postfix, arguments);
        perform_calculations(intqueue, postfix, arguments);
    }
    return 0;
}

