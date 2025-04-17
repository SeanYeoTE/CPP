#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include "../includes/AForm.hpp"
# include "../includes/Bureaucrat.hpp"
# include <iostream>
# include <string>

class RobotomyRequestForm : public AForm
{
    public:
        RobotomyRequestForm();
        RobotomyRequestForm(RobotomyRequestForm const &src);
        ~RobotomyRequestForm();
        RobotomyRequestForm &operator=(RobotomyRequestForm const &rhs);

        RobotomyRequestForm(std::string target);

        void beSigned(int grade);
        void execute(Bureaucrat const &executor) const;

    private:
		std::string _target;
};

#endif