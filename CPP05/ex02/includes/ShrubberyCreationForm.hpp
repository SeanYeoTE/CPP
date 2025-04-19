#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include "../includes/AForm.hpp" // Ensure this is included for the base class
# include "../includes/Bureaucrat.hpp"
# include <iostream>
# include <string>

class ShrubberyCreationForm : public AForm
{
  public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(ShrubberyCreationForm const &src);
	~ShrubberyCreationForm();
	ShrubberyCreationForm &operator=(ShrubberyCreationForm const &rhs);

	ShrubberyCreationForm(std::string target);

	void execute(Bureaucrat const &executor) const;

  private:
	std::string _target;
};

#endif /* ******************************************* SHRUBBERYCREATIONFORM_H */