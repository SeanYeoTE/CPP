#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>

class	Bureaucrat;

class AForm
{
  public:
	AForm();
	AForm(std::string name, int gradeToSign, int gradeToExecute);
	AForm(AForm const &src);
	virtual ~AForm();
	AForm &operator=(AForm const &rhs);

	const std::string &getName() const;
	const bool &getIsSigned() const;
	const int &getGradeToSign() const;
	const int &getGradeToExecute() const;
	void setIsSigned(bool ran);

	void beSigned(int grade);
	virtual void execute(Bureaucrat const &executor) const = 0;

	class FormException : public std::exception
	{
		public:
		virtual const char *what() const throw() = 0;
		virtual ~FormException() throw()
		{
		}
	};

	class GradeTooHighException : public FormException
	{
		public:
		virtual const char *what() const throw();
	};
	class GradeTooLowException : public FormException
	{
		public:
		virtual const char *what() const throw();
	};
	class FormNotSignedException : public FormException
	{
		public:
		virtual const char *what() const throw();
	};

  private:
	const std::string _name;
	bool _isSigned;
	int _gradeToSign;
	int _gradeToExecute;
};

std::ostream &operator<<(std::ostream &o, AForm const &i);

#endif /* ************************************************************ FORM_H */
