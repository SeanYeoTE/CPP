/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:59:07 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/13 15:48:57 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main(void)
{
	Fixed	a;
	Fixed	zero;

	Fixed const b(Fixed(5.05f) * Fixed(2));
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max(a, b) << std::endl;
	// Additional test cases for unused operators
	std::cout << "\n----- Testing Comparison Operators -----" << std::endl;
	Fixed c(42.42f);
	Fixed d(42.42f);
	Fixed e(21.21f);
	std::cout << "c: " << c << ", d: " << d << ", e: " << e << std::endl;
	std::cout << "c > e: " << (c > e) << std::endl;
	std::cout << "c < e: " << (c < e) << std::endl;
	std::cout << "c >= d: " << (c >= d) << std::endl;
	std::cout << "c <= e: " << (c <= e) << std::endl;
	std::cout << "c == d: " << (c == d) << std::endl;
	std::cout << "c != e: " << (c != e) << std::endl;
	std::cout << "\n----- Testing Arithmetic Operators -----" << std::endl;
	std::cout << "c + e = " << (c + e) << std::endl;
	std::cout << "c - e = " << (c - e) << std::endl;
	std::cout << "c * e = " << (c * e) << std::endl;
	std::cout << "c / e = " << (c / e) << std::endl;
	// Test division by zero
	std::cout << "\nDivision by zero: c / zero = " << (c / zero) << std::endl;
	std::cout << "c / 0 = " << (c / Fixed(0)) << std::endl;
	std::cout << "\n----- Testing Increment Operators -----" << std::endl;
	Fixed f(10.5f);
	std::cout << "f: " << f << std::endl;
	std::cout << "++f: " << ++f << std::endl;
	std::cout << "f: " << f << std::endl;
	std::cout << "f++: " << f++ << std::endl;
	std::cout << "f: " << f << std::endl;
	std::cout << "\n----- Testing Decrement Operators -----" << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "--c: " << --c << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "c--: " << c-- << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "\n----- Testing min Function -----" << std::endl;
	std::cout << "Fixed::min(c, e): " << Fixed::min(c, e) << std::endl;
	return (0);
}
