#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal
{
  public:
	WrongAnimal();
	WrongAnimal(WrongAnimal const &src);
	~WrongAnimal();

	WrongAnimal &operator=(WrongAnimal const &rhs);

	void setType(std::string type);
	std::string getType() const;
	void makeSound() const;

  protected:
	std::string _type;
};

#endif /* ***************************************************** WRONGANIMAL_H */