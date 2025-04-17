#include "../includes/ShrubberyCreationForm.hpp"
#include <fstream>
#include <iostream>

ShrubberyCreationForm::ShrubberyCreationForm(void) : AForm("ShrubberyCreationForm",
	145, 137), _target("No Target")
{
	std::cout << "ShrubberyCreationForm default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string name) : AForm("ShrubberyCreationForm",
	145, 137), _target(name)
{
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other),
	_target(other._target)
{
	std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	std::cout << "ShrubberyCreationForm assignment operator called" << std::endl;
	_target = other._target;
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

// beSigned Method
void ShrubberyCreationForm::beSigned(int grade)
{
	if (grade > this->getGradeToSign())
		throw AForm::GradeTooLowException();
	this->setIsSigned(true);
}

// execute Method
void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (!this->getIsSigned())
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->getGradeToExecute())
		throw AForm::GradeTooLowException();

	try
	{
		std::ofstream ofs;
		ofs.open((this->_target + "_shrubbery").c_str());
			// Use .c_str() for conversion
		ofs << "              _{\\ _{\\{\\/}/}/}__" << std::endl;
		ofs << "             {/{/\\}{/{/\\}(\\}{/\\} _" << std::endl;
		ofs << "            {/{/\\}{/{/\\}(_)\\}{/{/\\}  _" << std::endl;
		ofs << "         {\\{/(\\"
			<< "}\\}{/{/\\}\\}{/){/\\}\\} /\\}" << std::endl;
		ofs << "        {/{/(_)/}{\\{/)\\"
			<< "}{\\(_){/}/}/}/}" << std::endl;
		ofs << "       _{\\{/{/{\\{/{/(_)/}/}/}{\\(/}/}/}" << std::endl;
		ofs << "      {/{/{\\{\\{\\(/}{\\{\\/}/}{\\}(_){\\/}\\}" << std::endl;
		ofs << "      _{\\{/{\\{/(_)/}{/{/{/\\}\\})\\}{/\\}" << std::endl;
		ofs << "     {/{/{\\{\\(/}{/{\\{\\{\\/})/}{\\(_)/}/}\\}" << std::endl;
		ofs << "      {\\{\\/}(_){\\{\\{\\/}/}(_){\\/}{\\/}/})/}" << std::endl;
		ofs << "       {/{\\{\\/}{/{\\{\\{\\/}/}{\\{\\/}/}\\}(_)" << std::endl;
		ofs << "      {/{\\{\\/}{/){\\{\\{\\/}/}{\\{\\(/}/}\\}/}" << std::endl;
		ofs << "       {/{\\{\\/}(_){\\{\\{\\(/}/}{\\(_)/}/}\\}" << std::endl;
		ofs << "         {/({/{\\{/{\\{\\/}(_){\\/}/}\\}/}(\\}" << std::endl;
		ofs << "          (_){/{\\/}{\\{\\/}/}{\\{\\)/}/}(_)" << std::endl;
		ofs << "            {/{/{\\{\\/}{/{\\{\\{\\(_)/}" << std::endl;
		ofs << "             {/{\\{\\{\\/}/}{\\{\\\\}/}" << std::endl;
		ofs << "              {){/ {\\/}{\\/} \\}\\}" << std::endl;
		ofs << "              (_)  \\.-'.-/" << std::endl;
		ofs << "          __...--- |'-.-'| --...__" << std::endl;
		ofs << "   _...--\"   .-'   |'-.-'|  ' -.  \"\"--..__" << std::endl;
		ofs << " -\"    ' .  . '    |.'-._| '  . .  '   jro" << std::endl;
		ofs << " .  '-  '    .--'  | '-.'|    .  '  . '" << std::endl;
		ofs << "          ' ..     |'-_.-|" << std::endl;
		ofs << "  .  '  .       _.-|-._ -|-._  .  '  . " << std::endl;
		ofs << "              .'   |'- .-|   '." << std::endl;
		ofs << "  ..-'   ' .  '.   `-._.-’   .'  '  - ." << std::endl;
		ofs << "   .-' '        '-._______.-'     '  ." << std::endl;
		ofs << "        .      ~," << std::endl;
		ofs << "    .       .   |\\   .    ' '-." << std::endl;
		ofs << "    ___________/  \\____________" << std::endl;
		ofs << "   /  Why is it, when you want \\" << std::endl;
		ofs << "  |  something, it is so damn   |" << std::endl;
		ofs << "  |    much work to get it?     |" << std::endl;
		ofs << "   \\___________________________/" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "error opening file" << std::endl;
	}
}
