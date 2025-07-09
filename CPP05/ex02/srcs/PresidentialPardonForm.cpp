#include "../includes/PresidentialPardonForm.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm() 
    : AForm("PresidentialPardonForm", 25, 5), _target("") {}

PresidentialPardonForm::PresidentialPardonForm(std::string target) 
    : AForm("PresidentialPardonForm", 25, 5), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &src) 
    : AForm(src), _target(src._target) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &rhs) {
    if (this != &rhs) {
        AForm::operator=(rhs);
        _target = rhs._target;
    }
    return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
    if (!this->getIsSigned())
        throw AForm::FormNotSignedException();
    if (executor.getGrade() > this->getGradeToExecute())
        throw AForm::GradeTooLowException();
    
    std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
