/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:19:17 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/25 14:07:12 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

void openfile(std::string filename)
{
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    
    int c = infile.get();
    while (c != std::ifstream::traits_type::eof()) {
        std::cout << c;
        c = infile.get();
    }
    
}

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Error: Invalid arguments" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    openfile(filename);
    return 0;
}