#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

// #include <cstdlib>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>

class BitcoinExchange {
    private:
        std::map<std::string, std::string> _data;

        std::string trim(const std::string &str);
        bool valid_date(const std::string &date);
        void validate_value(const std::string &value);
        void processLine(const std::string& date, const std::string& value);
        double findExchangeRate(const std::string& date);


    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void run(const std::string filename);
};

#endif
