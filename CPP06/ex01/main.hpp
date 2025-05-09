#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>
#include <stdint.h>

class Data
{
    public:
        Data();
        ~Data();
        Data(const Data &src);
        Data &operator=(const Data &src);

        std::string getName() const;
        int getAge() const;

    private:
        std::string name;
        int age;
};

class Serializer
{
    private:
        Serializer();
        ~Serializer();
        Serializer(const Serializer &src);
        Serializer &operator=(const Serializer &src);

    public:
        static uintptr_t serialize(Data *ptr);
        static Data *deserialize(uintptr_t raw);
};


#endif