#ifndef KEEPER_H
#define KEEPER_H
#include "Base.h"
#include <string>

// Контейнер (ВУЗ): динамический массив указателей на производные объекты Base
class Keeper
{
    Base **items;
    int count, capacity;
    void grow();
    void clear();

public:
    Keeper();
    Keeper(const Keeper &o);
    ~Keeper();
    Keeper &operator=(const Keeper &o);

    int size() const;
    void add(Base *obj); // Keeper становится владельцем объекта
    void remove(int index);
    Base &operator[](int index);
    const Base &operator[](int index) const;
    void print(std::ostream &os) const;
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);
};
std::ostream &operator<<(std::ostream &os, const Keeper &k);
#endif
