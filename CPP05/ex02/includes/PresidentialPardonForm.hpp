#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "../includes/AForm.hpp"
# include "../includes/Bureaucrat.hpp"
# include <iostream>
# include <string>

class PresidentialPardonForm : public AForm
{
  public:
	PresidentialPardonForm();
	PresidentialPardonForm(std::string target);
	PresidentialPardonForm(PresidentialPardonForm const &src);
	~PresidentialPardonForm();
	PresidentialPardonForm &operator=(PresidentialPardonForm const &rhs);

	void execute(Bureaucrat const &executor) const;

  private:
	std::string _target;
};

#endif
