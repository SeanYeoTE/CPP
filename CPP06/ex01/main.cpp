#include "main.hpp"

Data::Data() : name("Default"), age(0)
{
    std::cout << "Data constructor called" << std::endl;
}

Data::~Data()
{
    std::cout << "Data destructor called" << std::endl;
}
Data::Data(const Data &src)
{
    std::cout << "Data copy constructor called" << std::endl;
    *this = src;
}
Data &Data::operator=(const Data &src)
{
    std::cout << "Data assignment operator called" << std::endl;
    if (this != &src)
    {
        this->name = src.name;
        this->age = src.age;
    }
    return *this;
}

std::string Data::getName() const
{
    return this->name;
}

int Data::getAge() const
{
    return this->age;
}

uintptr_t Serializer::serialize(Data *ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data *>(raw);
}

int main(void)
{
    Data *data = new Data();
    uintptr_t raw = Serializer::serialize(data);
    Data *deserializedData = Serializer::deserialize(raw);

    std::cout << "Original Data Address: " << data << std::endl;
    std::cout << "Original Data Name: " << data->getName() << std::endl;
    std::cout << "Original Data Age: " << data->getAge() << std::endl;
    std::cout << std::endl;
    std::cout << "Serialized Raw Value: " << raw << std::endl;
    std::cout << std::endl;
    std::cout << "Deserialized Data Address: " << deserializedData << std::endl;
    std::cout << "Deserialized Data Name: " << deserializedData->getName() << std::endl;
    std::cout << "Deserialized Data Age: " << deserializedData->getAge() << std::endl;

    delete data;
    return 0;
}