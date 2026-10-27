#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "Exceptions.h"
#include "Utils.h"
#include <fstream>
using namespace std;

Keeper::Keeper() : items(0), count(0), capacity(0) { cout << "[Конструктор без параметров] Keeper" << endl; }
Keeper::Keeper(const Keeper &o) : items(0), count(0), capacity(0)
{
    cout << "[Конструктор копирования] Keeper" << endl;
    for (int i = 0; i < o.count; ++i)
        add(o.items[i]->clone());
}
Keeper::~Keeper()
{
    clear();
    cout << "[Деструктор] Keeper" << endl;
}

Keeper &Keeper::operator=(const Keeper &o)
{
    if (this != &o)
    {
        Keeper tmp(o); // копия; при исключении текущее состояние не портится
        Base **p = items;
        items = tmp.items;
        tmp.items = p;
        int c = count;
        count = tmp.count;
        tmp.count = c;
        c = capacity;
        capacity = tmp.capacity;
        tmp.capacity = c;
    }
    return *this;
}
void Keeper::clear()
{
    for (int i = 0; i < count; ++i)
        delete items[i];
    delete[] items;
    items = 0;
    count = capacity = 0;
}
void Keeper::grow()
{
    int nc = capacity ? capacity * 2 : 4;
    Base **a = new Base *[nc];
    for (int i = 0; i < count; ++i)
        a[i] = items[i];
    delete[] items;
    items = a;
    capacity = nc;
}
int Keeper::size() const { return count; }
void Keeper::add(Base *obj)
{
    if (!obj)
        throw InputException("нельзя добавить пустой указатель");
    if (count == capacity)
        grow();
    items[count++] = obj;
}
void Keeper::remove(int index)
{
    if (index < 0 || index >= count)
        throw IndexException("нет элемента с номером " + to_string(index + 1));
    delete items[index];
    for (int i = index; i < count - 1; ++i)
        items[i] = items[i + 1];
    --count;
}
Base &Keeper::operator[](int index)
{
    if (index < 0 || index >= count)
        throw IndexException("нет элемента с номером " + to_string(index + 1));
    return *items[index];
}
const Base &Keeper::operator[](int index) const
{
    if (index < 0 || index >= count)
        throw IndexException("нет элемента с номером " + to_string(index + 1));
    return *items[index];
}
void Keeper::print(ostream &os) const
{
    if (count == 0)
    {
        os << "ВУЗ пуст." << endl;
        return;
    }
    for (int i = 0; i < count; ++i)
        os << (i + 1) << ") " << *items[i] << endl;
}
ostream &operator<<(ostream &os, const Keeper &k)
{
    k.print(os);
    return os;
}

void Keeper::saveToFile(const string &filename) const
{
    ofstream out(filename.c_str());
    if (!out)
        throw FileException("не удалось открыть '" + filename + "' для записи");
    out << count << '\n';
    for (int i = 0; i < count; ++i)
    {
        out << items[i]->type() << '\n';
        items[i]->save(out);
    }
    if (!out)
        throw FileException("ошибка записи в '" + filename + "'");
}
void Keeper::loadFromFile(const string &filename)
{
    ifstream in(filename.c_str());
    if (!in)
        throw FileException("не удалось открыть '" + filename + "' для чтения");
    Keeper tmp; // читаем во временный контейнер
    int n = parseInt(getLineFrom(in));
    if (n < 0)
        throw FormatException("отрицательное количество записей");
    for (int i = 0; i < n; ++i)
    {
        int t = parseInt(getLineFrom(in));
        Base *obj = 0;
        if (t == 1)
            obj = new Student();
        else if (t == 2)
            obj = new Teacher();
        else if (t == 3)
            obj = new Admin();
        else
            throw FormatException("неизвестный тип записи: " + to_string(t));
        try
        {
            obj->load(in);
            tmp.add(obj);
        }
        catch (...)
        {
            delete obj;
            throw;
        }
    }
    Base **p = items;
    items = tmp.items;
    tmp.items = p; // обмен: tmp удалит старое содержимое
    int c = count;
    count = tmp.count;
    tmp.count = c;
    c = capacity;
    capacity = tmp.capacity;
    tmp.capacity = c;
}
