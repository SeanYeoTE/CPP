#include "../includes/BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {
    std::ifstream file("data.csv");
    std::string line;

    std::getline(file, line);
    while (std::getline(file, line))
    {
        size_t delimiter = line.find(',');
        std::string date = trim(line.substr(0, delimiter));
        std::string value = trim(line.substr(delimiter + 1, line.length()));

        _data[date] = value;
    }
    file.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator= (const BitcoinExchange &other)
{
    if (this != &other)
    {
        _data = other._data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}


std::string BitcoinExchange::trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;
    
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool BitcoinExchange::valid_date(const std::string &date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    std::string year = date.substr(0, 4);
    std::string month = date.substr(5, 2);
    std::string day = date.substr(8, 2);

    int monthInt, dayInt;
    
    // Check if strings contain only digits
    for (size_t i = 0; i < year.length(); i++) {
        if (!std::isdigit(year[i])) return false;
    }
    for (size_t i = 0; i < month.length(); i++) {
        if (!std::isdigit(month[i])) return false;
    }
    for (size_t i = 0; i < day.length(); i++) {
        if (!std::isdigit(day[i])) return false;
    }
    
    // yearInt = std::atoi(year.c_str());
    monthInt = std::atoi(month.c_str());
    dayInt = std::atoi(day.c_str());
    
    // if (yearInt < 1000 || yearInt > 9999)
    //     return false;
    if (monthInt < 1 || monthInt > 12)
        return false;
    if (dayInt < 1 || dayInt > 31)
        return false;
    return true;
}

void BitcoinExchange::validate_value(const std::string &value)
{
    // Check if the string is a valid number format
    bool hasDecimal = false;
    bool hasDigit = false;
    size_t start = 0;
    
    // Skip leading whitespace (should already be trimmed, but just in case)
    // while (start < value.length() && std::isspace(value[start]))
    //     start++;
    
    // Check for optional + or - sign
    if (start < value.length() && (value[start] == '+' || value[start] == '-'))
        start++;
    
    // Check each character
    for (size_t i = start; i < value.length(); i++) {
        if (std::isdigit(value[i])) {
            hasDigit = true;
        } else if (value[i] == '.' && !hasDecimal) {
            hasDecimal = true;
        } else {
            throw std::invalid_argument("not a number => " + value);
        }
    }
    
    if (!hasDigit) {
        throw std::invalid_argument("not a number => " + value);
    }
    
    // Convert to double using stringstream
    std::stringstream ss(value);
    double doubleValue;
    ss >> doubleValue;
    
    if (ss.fail() || !ss.eof()) {
        throw std::invalid_argument("not a number => " + value);
    }

    if (doubleValue < 0)
        throw std::invalid_argument("not a positive number.");
    if (doubleValue > 1000)
        throw std::invalid_argument("too large a number.");
}


void BitcoinExchange::run(const std::string filename)
{
    // check file;
    // file exists?
    // file cna open 
    std::ifstream file(filename.c_str());
    std::string line;

    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }
    if (file.peek() == std::ifstream::traits_type::eof())
    {
        std::cout << "Error: file is empty" << std::endl;
        return;
    }
    std::getline(file, line);
    if (line != "date | value") {
        std::cout << "Error: invalid file format" << std::endl;
        return;
    }

    // read loop here
    while (std::getline(file, line))
    {
        size_t delimiter = line.find('|');
        if (delimiter == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl; 
            continue;
        }
        std::string date = trim(line.substr(0, delimiter));
        std::string value = trim(line.substr(delimiter + 1));
        
        // Validate and process the line
        processLine(date, value);
    }
    file.close();
}

void BitcoinExchange::processLine(const std::string& date, const std::string& value)
{
    try {
        // Validate date format
        if (!valid_date(date)) {
            throw std::invalid_argument("bad input => " + date);
            return;
        }
        
        // Validate value
        if (value.empty()) {
            throw std::invalid_argument("bad input => " + value);
            return;
        }
        
        validate_value(value);
        
        // Find exchange rate and calculate result
        double exchangeRate = findExchangeRate(date);
        double inputValue = std::atof(value.c_str());
        double result = inputValue * exchangeRate;
        
        std::cout << date << " => " << value << " = " << result << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

double BitcoinExchange::findExchangeRate(const std::string& date)
{
    // Try to find exact match first
    std::map<std::string, std::string>::iterator it = _data.find(date);
    if (it != _data.end()) {
        return std::atof(it->second.c_str());
    }
    
    // Find the closest lower date
    it = _data.upper_bound(date);
    if (it == _data.begin()) {
        // Date is before all entries in database
        throw std::invalid_argument("date too early");
    }
    
    --it; // Get the largest date that is smaller than target
    return std::atof(it->second.c_str());
}
