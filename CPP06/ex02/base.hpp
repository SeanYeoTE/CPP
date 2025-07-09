#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
// #include <string>
// #include <stdint.h>

class Base
{
    public:
        virtual ~Base();
};

class A : public Base
{
    public:
        ~A();
};

class B : public Base
{
    public:
        ~B();
};

class C : public Base
{
    public:
        ~C();
};


#endif