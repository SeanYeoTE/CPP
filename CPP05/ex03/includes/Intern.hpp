#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
public:
    Intern();
    ~Intern();
    Intern(const Intern &src);
    Intern &operator=(const Intern& rhs);

    AForm *makeForm(std::string formname, std::string formtarget);
};

#endif
