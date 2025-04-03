#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"
# include <iostream>
# include <string>

class Dog : public Animal
{
  public:
	Dog();
	Dog(Dog const &src);
	~Dog();

	Dog &operator=(Dog const &rhs);

	void makeSound() const;
	Brain* getBrain() const;
	bool addIdea(std::string idea);
	std::string getIdea(int index) const;

  private:
	Brain* brain;
};

#endif /* ************************************************************* DOG_H */
