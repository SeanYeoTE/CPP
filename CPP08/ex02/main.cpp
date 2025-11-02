#include "MutantStack.hpp"
#include <iostream>
#include <vector>

// Extended test function definition
// int main()
// {
//     std::cout << "=== Extended MutantStack Test Cases ===\n\n";

//     // Test 1: Empty stack operations
//     std::cout << "Test 1: Empty stack\n";
//     MutantStack<int> emptyStack;
//     std::cout << "Empty stack size: " << emptyStack.size() << std::endl;
//     std::cout << "Empty stack is empty: " << (emptyStack.empty() ? "true" : "false") << std::endl;
//     std::cout << "Empty stack iterators: begin == end: " << (emptyStack.begin() == emptyStack.end() ? "true" : "false") << std::endl;
//     std::cout << std::endl;

//     // Test 2: Different data types
//     std::cout << "Test 2: String MutantStack\n";
//     MutantStack<std::string> strStack;
//     strStack.push("Hello");
//     strStack.push("World");
//     strStack.push("Mutant");
//     strStack.push("Stack");

//     std::cout << "String stack size: " << strStack.size() << std::endl;
//     std::cout << "String stack top: " << strStack.top() << std::endl;
//     strStack.pop();
//     std::cout << "After pop, string stack size: " << strStack.size() << std::endl;
//     std::cout << "String stack top: " << strStack.top() << std::endl;
//     std::cout << "String stack contents (reverse order due to stack): ";
//     MutantStack<std::string>::iterator it_str = strStack.begin();
//     for (; it_str != strStack.end(); ++it_str) {
//         std::cout << *it_str << " ";
//     }
//     std::cout << std::endl << std::endl;

//     // Test 3: Double MutantStack
//     std::cout << "Test 3: Double MutantStack\n";
//     MutantStack<double> doubleStack;
//     doubleStack.push(3.14);
//     doubleStack.push(2.71);
//     doubleStack.push(1.41);
//     doubleStack.push(0.577);

//     std::cout << "Double stack size: " << doubleStack.size() << std::endl;
//     std::cout << "Double stack top: " << doubleStack.top() << std::endl;
//     std::cout << "Double stack contents: ";
//     MutantStack<double>::iterator it_double = doubleStack.begin();
//     for (; it_double != doubleStack.end(); ++it_double) {
//         std::cout << *it_double << " ";
//     }
//     std::cout << std::endl << std::endl;

//     // Test 4: Large number of elements
//     std::cout << "Test 4: Large number of elements\n";
//     MutantStack<int> largeStack;
//     for (int i = 0; i < 1000; ++i) {
//         largeStack.push(i);
//     }
//     std::cout << "Large stack size: " << largeStack.size() << std::endl;
//     std::cout << "First 10 elements: ";
//     MutantStack<int>::iterator it_large = largeStack.begin();
//     for (int i = 0; i < 10 && it_large != largeStack.end(); ++i, ++it_large) {
//         std::cout << *it_large << " ";
//     }
//     std::cout << std::endl;
//     std::cout << "Last 10 elements (top of stack): ";
//     MutantStack<int>::iterator ite_large = largeStack.end();
//     for (int i = 0; i < 10 && ite_large != largeStack.begin(); ) {
//         --ite_large;
//         std::cout << *ite_large << " ";
//         ++i;
//     }
//     std::cout << std::endl << std::endl;

//     // Test 5: Converting to standard stack
//     std::cout << "Test 5: Converting to std::stack\n";
//     MutantStack<int> mutantStack;
//     mutantStack.push(10);
//     mutantStack.push(20);
//     mutantStack.push(30);

//     std::stack<int> standardStack(mutantStack);
//     std::cout << "Converting MutantStack to std::stack size: " << standardStack.size() << std::endl;
//     std::cout << "Standard stack top: " << standardStack.top() << std::endl;
//     standardStack.pop();
//     std::cout << "After pop, standard stack size: " << standardStack.size() << std::endl;
//     std::cout << std::endl;

   

//     // Test 6: Pop until empty
//     std::cout << "Test 6: Pop until empty\n";
//     MutantStack<int> popStack;
//     popStack.push(1);
//     popStack.push(2);
//     popStack.push(3);
//     popStack.push(4);
//     popStack.push(5);

//     std::cout << "Initial size: " << popStack.size() << std::endl;
//     while (!popStack.empty()) {
//         std::cout << "Top: " << popStack.top() << ", Size before pop: " << popStack.size();
//         popStack.pop();
//         std::cout << ", Size after pop: " << popStack.size() << std::endl;
//     }
//     std::cout << std::endl;

//     std::cout << "=== All Extended Tests Completed ===\n";

//     return 0;
// }


int main()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl;

    mstack.pop();

    std::cout << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    //[...]
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);
    return 0;
}

// int main()
// {
//     std::list<int> mstack;
//     mstack.push_front(5);
//     mstack.push_front(17);

//     std::cout << mstack.front() << std::endl;

//     mstack.pop_front();

//     std::cout << mstack.size() << std::endl;

//     mstack.push_front(3);
//     mstack.push_front(5);
//     mstack.push_front(737);
//     //[...]
//     mstack.push_front(0);
    
//     std::list<int>::iterator it = mstack.begin();
//     std::list<int>::iterator ite = mstack.end();

//     ++it;
//     --it;
//     while (it != ite)
//     {
//         --ite;
//         std::cout << *ite << std::endl;
//     }
//     std::list<int> s(mstack);
//     return 0;
// }
