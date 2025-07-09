#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <iostream>
# include <string>

class Animal
{
  public:
	Animal();
	Animal(Animal const &src);
	virtual ~Animal();

	Animal &operator=(Animal const &rhs);

	void setType(std::string type);
	std::string getType() const;
	virtual void makeSound() const = 0;

  protected:
	std::string type;
};

#endif /* ********************************************************** ANIMAL_H */