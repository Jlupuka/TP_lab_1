#include "Admin.h"
#include "Exceptions.h"
#include "Utils.h"
using namespace std;

Admin::Admin() : Base(), position(""), phone(""), area("") { cout << "[Конструктор без параметров] Admin" << endl; }
Admin::Admin(const string &f, const string &pos, const string &ph, const string &a) : Base(f)
{
    setPosition(pos);
    setPhone(ph);
    setArea(a);
    cout << "[Конструктор с параметрами] Admin" << endl;
}
Admin::Admin(const Admin &o) : Base(o), position(o.position), phone(o.phone), area(o.area)
{
    cout << "[Конструктор копирования] Admin" << endl;
}
Admin::~Admin() { cout << "[Деструктор] Admin" << endl; }
Admin &Admin::operator=(const Admin &o)
{
    if (this != &o)
    {
        fio = o.fio;
        position = o.position;
        phone = o.phone;
        area = o.area;
    }
    return *this;
}
bool Admin::operator==(const Admin &o) const
{
    return fio == o.fio && position == o.position && phone == o.phone && area == o.area;
}

const string &Admin::getPosition() const { return position; }
void Admin::setPosition(const string &p)
{
    if (p.empty())
        throw InputException("должность не может быть пустой");
    position = p;
}
const string &Admin::getPhone() const { return phone; }
void Admin::setPhone(const string &p)
{
    if (p.empty())
        throw InputException("телефон не может быть пустым");
    for (size_t i = 0; i < p.size(); ++i)
    {
        char c = p[i];
        if (!((c >= '0' && c <= '9') || c == '+' || c == '-' || c == ' ' || c == '(' || c == ')'))
            throw InputException("телефон содержит недопустимые символы");
    }
    phone = p;
}
const string &Admin::getArea() const { return area; }
void Admin::setArea(const string &a)
{
    if (a.empty())
        throw InputException("область ответственности не может быть пустой");
    area = a;
}

int Admin::type() const { return 3; }
const char *Admin::typeName() const { return "Административный персонал"; }
void Admin::print(ostream &os) const
{
    os << "Администрация: " << fio << ", должность: " << position << ", телефон: " << phone
       << ", область ответственности: " << area;
}
void Admin::input()
{
    setFio(readLine("ФИО: "));
    setPosition(readLine("Должность: "));
    setPhone(readLine("Телефон: "));
    setArea(readLine("Область ответственности: "));
}
void Admin::save(ostream &os) const
{
    os << fio << '\n'
       << position << '\n'
       << phone << '\n'
       << area << '\n';
}
void Admin::load(istream &is)
{
    setFio(getLineFrom(is));
    setPosition(getLineFrom(is));
    setPhone(getLineFrom(is));
    setArea(getLineFrom(is));
}
Base *Admin::clone() const { return new Admin(*this); }
