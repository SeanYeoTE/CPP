#include "MateriaSource.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

MateriaSource::MateriaSource() : _index(0)
{
	std::cout << "MateriaSource default constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
		this->_materia[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource &src) : _index(0)
{
	std::cout << "MateriaSource copy constructor called" << std::endl;
	
	// Initialize materia to NULL
	for (int i = 0; i < 4; i++)
		this->_materia[i] = NULL;
	
	// Copy materia from src
	for (int i = 0; i < 4; i++)
	{
		if (src._materia[i])
		{
			this->_materia[i] = src._materia[i]->clone();
			this->_index++;
		}
	}
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

MateriaSource::~MateriaSource()
{
	std::cout << "MateriaSource destructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (this->_materia[i])
			delete this->_materia[i];
	}
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

MateriaSource &MateriaSource::operator=(MateriaSource const &rhs)
{
	std::cout << "MateriaSource assignation operator called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (this->_materia[i])
			delete this->_materia[i];
	}
	for (int i = 0; i < 4; i++)
	{
		if (rhs._materia[i])
			this->_materia[i] = rhs._materia[i]->clone();
		else
			this->_materia[i] = NULL;
	}
	this->_index = rhs._index;
	return (*this);
}

/*
** --------------------------------- METHODS ----------------------------------
*/
void MateriaSource::learnMateria(AMateria *m)
{
	// std::cout << "Learning materia, current _index: " << this->_index << std::endl;
	if (m && this->_index < 4)
	{
		// std::cout << "Learning materia of type: " << m->getType() << " at index " << this->_index << std::endl;
		this->_materia[this->_index] = m;
		this->_index++;
		// std::cout << "Materia " << m->getType() << " learned, new _index: " << this->_index << std::endl;
	}
	else if (!m)
	{
		// std::cout << "Cannot learn NULL materia" << std::endl;
	}
	else
	{
		// std::cout << "MateriaSource is full" << std::endl;
	}
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < this->_index; i++)
	{
		if (this->_materia[i])
		{
			// std::cout << "Materia at index " << i << " is of type: " << this->_materia[i]->getType() << std::endl;
			if (this->_materia[i]->getType() == type)
			{
				// std::cout << "Materia " << type << " created" << std::endl;
				return (this->_materia[i]->clone());
			}
		}
		else
		{
			// std::cout << "Materia at index " << i << " is NULL" << std::endl;
		}
	}
	// std::cout << "Materia " << type << " not found" << std::endl;
	return (NULL);
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
