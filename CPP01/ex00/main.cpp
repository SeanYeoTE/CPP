/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:44:52 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/21 17:54:41 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    // Create a zombie on the heap
    Zombie* heapZombie = newZombie("Heapy");
    heapZombie->announce();

    // Create a zombie on the stack
    randomChump("Stacky");

    // Clean up heap-allocated zombie
    delete heapZombie;

    return 0;
}
