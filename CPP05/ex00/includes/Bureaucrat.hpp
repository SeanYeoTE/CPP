#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>

class Bureaucrat
{

	public:

		Bureaucrat();
		Bureaucrat( Bureaucrat const & src );
		~Bureaucrat();
		Bureaucrat &		operator=( Bureaucrat const & rhs );
		Bureaucrat(std::string name, int grade);

		const std::string & getName() const;
		int getGrade() const;

		void incrementGrade();
		void decrementGrade();

		// Exceptions
		class BureaucratException : public std::exception
		{
			public:
				virtual const char* what() const throw() = 0;
				virtual ~BureaucratException() throw() {}
		};

		class GradeTooHighException : public BureaucratException
		{
			public:
					virtual const char* what() const throw();
		};
		class GradeTooLowException : public BureaucratException
		{
			public:
					virtual const char* what() const throw();
		};

	private:
		const std::string _name;
		int _grade;

};

std::ostream &			operator<<( std::ostream & o, Bureaucrat const & i );

#endif /* ****************************************************** BUREAUCRAT_H */