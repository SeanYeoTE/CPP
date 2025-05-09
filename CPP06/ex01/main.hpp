#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>
#include <stdint.h>

class Data;

class Data
{
    public:
        Data();
        ~Data();
        Data(const Data &src);
        Data &operator=(const Data &src);
        Data(std::string name, int age);

        std::string getName() const;
        int getAge() const;
        Data *getNext() const;

    private:
        std::string name;
        int age;
        Data *next;
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