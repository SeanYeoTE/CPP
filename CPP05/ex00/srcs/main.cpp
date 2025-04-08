#include "Bureaucrat.hpp"
#include <iostream>
#include <string>
#include <exception>


int main()
{
    try
    {
        Bureaucrat b("John", 1);
        std::cout << b << std::endl;
        b.incrementGrade();
    }
    catch (const Bureaucrat::BureaucratException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    try
    {
        Bureaucrat c("Doe", 150);
        std::cout << c << std::endl;
        c.decrementGrade();
    }
    catch (const Bureaucrat::BureaucratException& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}