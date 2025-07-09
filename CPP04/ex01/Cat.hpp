#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"
# include <iostream>
# include <string>

class Cat : public Animal
{
  public:
	Cat();
	Cat(Cat const &src);
	~Cat();

	Cat &operator=(Cat const &rhs);

	void makeSound() const;
	Brain* getBrain() const;
	virtual bool addIdea(std::string idea);
	virtual std::string getIdea(int index) const;

  private:
	Brain* brain;
};


#endif /* ************************************************************* CAT_H */
