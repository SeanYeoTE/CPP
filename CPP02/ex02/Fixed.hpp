#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <string>
# include <cmath>

class Fixed
{

	public:

		Fixed();
		Fixed( Fixed const & src );
		Fixed(const int value);
		Fixed(const float value);
		~Fixed();
		
		Fixed &		operator=( Fixed const & rhs );

		bool 	operator>( Fixed const & rhs );
		bool 	operator<( Fixed const & rhs );
		bool 	operator>=( Fixed const & rhs );
		bool 	operator<=( Fixed const & rhs );
		bool 	operator==( Fixed const & rhs );
		bool 	operator!=( Fixed const & rhs );
		
		Fixed  operator+( Fixed const & rhs ) const;
		Fixed  operator-( Fixed const & rhs ) const;
		Fixed  operator*( Fixed const & rhs ) const;
		Fixed  operator/( Fixed const & rhs ) const;

		Fixed 		operator++(int);
		Fixed 		operator--(int);
		Fixed & 	operator++();
		Fixed & 	operator--();

		int getRawBits( void ) const;
		void setRawBits( int const raw );
		int toInt( void ) const;
		float toFloat( void ) const;

		Fixed *min( Fixed & a, Fixed & b );
		const Fixed *min( Fixed const & a, Fixed const & b );
		Fixed *max( Fixed & a, Fixed & b );
		const Fixed *max( Fixed const & a, Fixed const & b );
	
	private:
		int _value;
		static const int _fractionalBits = 8;
		


};

std::ostream &			operator<<( std::ostream & o, Fixed const & i );

#endif /* *********************************************************** FIXED_H */