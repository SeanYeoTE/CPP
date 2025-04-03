#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>
# include <sstream>

class Brain
{
  public:
	Brain();
	Brain(Brain const &src);
	~Brain();

	Brain &operator=(Brain const &rhs);
	
	bool addIdea(std::string idea);
	std::string getIdea(int index) const;
	
	std::string ideas[100];
};

#endif /* ********************************************************** BRAIN_H */
