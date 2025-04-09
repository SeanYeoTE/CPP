#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>

class Form
{

	public:

		Form();
		Form( std::string name, int gradeToSign, int gradeToExecute );
		Form( Form const & src );
		~Form();
		Form &		operator=( Form const & rhs );


		const std::string & getName() const;
		const bool & getIsSigned() const;
		const int & getGradeToSign() const;
		const int & getGradeToExecute() const;
		void beSigned(int grade);
		
		class FormException : public std::exception
		{
			public:
				virtual const char* what() const throw() = 0;
				virtual ~FormException() throw() {}
		};

		class GradeTooHighException : public FormException
		{
			public:
					virtual const char* what() const throw();
		};
		class GradeTooLowException : public FormException
		{
			public:
					virtual const char* what() const throw();
		};

	private:
		const std::string _name;
		bool _isSigned;
		int _gradeToSign;
		int _gradeToExecute;

};

std::ostream &			operator<<( std::ostream & o, Form const & i );

#endif /* ************************************************************ FORM_H */