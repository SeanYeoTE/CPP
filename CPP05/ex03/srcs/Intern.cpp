#include "../includes/Intern.hpp"


Intern::Intern() {}

Intern::~Intern() {}


Intern::Intern(const Intern &src)
{
    *this = src;
}

Intern& Intern::operator=(const Intern& rhs)
{
    (void)rhs;
    return (*this);
}

AForm *Intern::makeForm(std::string formname, std::string formtarget)
{
    std::string names[] = {
        "shrubbery",
        "robotomy",
        "presidential"
    };
    
    for (int i = 0; i < 3; i++) {
        if (formname == names[i]) {
            std::cout << "Intern creates " << formname << " form" << std::endl;
            switch (i) {
                case 0:
                    return new ShrubberyCreationForm(formtarget);
                case 1:
                    return new RobotomyRequestForm(formtarget);
                case 2:
                    return new PresidentialPardonForm(formtarget);
            }
        }
    }
    std::cout << "Intern cannot create " << formname << " form" << std::endl;
    return NULL;
}
