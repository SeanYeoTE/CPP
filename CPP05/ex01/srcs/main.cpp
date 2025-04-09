#include "../includes/Bureaucrat.hpp"
#include "../includes/Form.hpp"
#include <iostream>
#include <string>
#include <exception>


int main()
{
    // try
    // {
    //     Bureaucrat b("John", 1);
    //     std::cout << b << std::endl;
    //     b.incrementGrade();
    // }
    // catch (const Bureaucrat::BureaucratException& e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }
    
    // try
    // {
    //     Bureaucrat c("Doe", 150);
    //     std::cout << c << std::endl;
    //     c.decrementGrade();
    // }
    // catch (const Bureaucrat::BureaucratException& e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }


    try
    {
        Form f("Form1", 1, 150);
        std::cout << f << std::endl;
        f.beSigned(1);
        std::cout << f << std::endl;
    }
    catch (const Form::FormException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    try
    {
        Form g("Form2", 150, 1);
        std::cout << g << std::endl;
        g.beSigned(150);
        std::cout << g << std::endl;
    }
    catch (const Form::FormException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    try
    {
        Form h("Form3", 151, 1);
        std::cout << h << std::endl;
    }
    catch (const Form::FormException& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}