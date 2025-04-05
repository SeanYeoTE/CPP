#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include <iostream>
# include <string>
# include "AMateria.hpp"
# include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{

	public:

		MateriaSource();
		MateriaSource( MateriaSource const & src );
		~MateriaSource();
		MateriaSource &		operator=( MateriaSource const & rhs );

		void learnMateria( AMateria *m );
		AMateria* createMateria( std::string const & type );

	private:
		AMateria *	_materia[4];
		int			_index;

};

#endif /* *************************************************** MATERIASOURCE_H */