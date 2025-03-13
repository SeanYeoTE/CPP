#include "Fixed.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Fixed::Fixed() : _value(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value)
{
	// std::cout << "Int constructor called" << std::endl;
	this->_value = value << this->_fractionalBits;
}

Fixed::Fixed(const float value)
{
	// std::cout << "Float constructor called" << std::endl;
	this->_value = roundf(value * (1 << this->_fractionalBits));
}

Fixed::Fixed(const Fixed &src)
{
	// std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Fixed::~Fixed()
{
	// std::cout << "Destructor called" << std::endl;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Fixed &Fixed::operator=(Fixed const &rhs)
{
	if (this != &rhs)
	{
		// std::cout << "Copy assignment operator called" << std::endl;
		this->_value = rhs.getRawBits();
	}
	return (*this);
}

bool Fixed::operator>(Fixed const &rhs)
{
	return (this->toFloat() > rhs.toFloat());
}

bool Fixed::operator<(Fixed const &rhs)
{
	return (this->toFloat() < rhs.toFloat());
}

bool Fixed::operator>=(Fixed const &rhs)
{
	return (this->toFloat() >= rhs.toFloat());
}

bool Fixed::operator<=(Fixed const &rhs)
{
	return (this->toFloat() <= rhs.toFloat());
}

bool Fixed::operator==(Fixed const &rhs)
{
	return (this->toFloat() == rhs.toFloat());
}

bool Fixed::operator!=(Fixed const &rhs)
{
	return (this->toFloat() != rhs.toFloat());
}

Fixed Fixed::operator+(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() + rhs.toFloat()));
}

Fixed Fixed::operator-(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() - rhs.toFloat()));
}

Fixed Fixed::operator*(Fixed const &rhs) const
{
	return (Fixed(this->toFloat() * rhs.toFloat()));
}

Fixed Fixed::operator/(Fixed const &rhs) const
{
	if (rhs.getRawBits() == 0)
	{
		return (Fixed(0));
	}
	return (Fixed(this->toFloat() / rhs.toFloat()));
}

// postfix
Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);
	this->_value++;
	return (tmp);
}

// postfix
Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);
	this->_value--;
	return (tmp);
}

// prefix
Fixed &Fixed::operator++()
{
	this->_value++;
	return (*this);
}

// prefix
Fixed &Fixed::operator--()
{
	this->_value--;
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Fixed const &i)
{
	std::cout << i.toFloat();
	return (o);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if (a.toFloat() < b.toFloat())
		return (a);
	return (b);
}

const Fixed &Fixed::min(Fixed const &a, Fixed const &b)
{
	if (a.toFloat() < b.toFloat())
		return (a);
	return (b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if (a.toFloat() > b.toFloat())
		return (a);
	return (b);
}

const Fixed &Fixed::max(Fixed const &a, Fixed const &b)
{
	if (a.toFloat() > b.toFloat())
		return (a);
	return (b);
}
/*
** --------------------------------- METHODS ----------------------------------
*/
int Fixed::getRawBits(void) const
{
	return (this->_value);
}

void Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}
int Fixed::toInt(void) const
{
	return (this->_value >> this->_fractionalBits);
}

float Fixed::toFloat(void) const
{
	return ((float)this->_value / (1 << this->_fractionalBits));
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
