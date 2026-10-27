#include "Student.h"
#include "Exceptions.h"
#include "Utils.h"
using namespace std;

Student::Student() : Base(), group(""), specialty(""), course(1), gpa(0)
{
    cout << "[Конструктор без параметров] Student" << endl;
}
Student::Student(const string &f, const string &g, const string &s, int c, double a) : Base(f)
{
    setGroup(g);
    setSpecialty(s);
    setCourse(c);
    setGpa(a);
    cout << "[Конструктор с параметрами] Student" << endl;
}
Student::Student(const Student &o) : Base(o), group(o.group), specialty(o.specialty), course(o.course), gpa(o.gpa)
{
    cout << "[Конструктор копирования] Student" << endl;
}
Student::~Student() { cout << "[Деструктор] Student" << endl; }

Student &Student::operator=(const Student &o)
{
    if (this != &o)
    {
        fio = o.fio;
        group = o.group;
        specialty = o.specialty;
        course = o.course;
        gpa = o.gpa;
    }
    return *this;
}
bool Student::operator==(const Student &o) const
{
    return fio == o.fio && group == o.group && specialty == o.specialty && course == o.course && gpa == o.gpa;
}

const string &Student::getGroup() const { return group; }
void Student::setGroup(const string &g)
{
    if (g.empty())
        throw InputException("группа не может быть пустой");
    group = g;
}
const string &Student::getSpecialty() const { return specialty; }
void Student::setSpecialty(const string &s)
{
    if (s.empty())
        throw InputException("специальность не может быть пустой");
    specialty = s;
}
int Student::getCourse() const { return course; }
void Student::setCourse(int c)
{
    if (c < 1 || c > 6)
        throw InputException("курс должен быть от 1 до 6");
    course = c;
}
double Student::getGpa() const { return gpa; }
void Student::setGpa(double g)
{
    if (g < 0 || g > 5)
        throw InputException("средний балл должен быть от 0 до 5");
    gpa = g;
}

int Student::type() const { return 1; }
const char *Student::typeName() const { return "Студент"; }
void Student::print(ostream &os) const
{
    os << "Студент: " << fio << ", группа " << group << ", специальность: " << specialty
       << ", курс " << course << ", средний балл " << gpa;
}
void Student::input()
{
    setFio(readLine("ФИО: "));
    setGroup(readLine("Группа: "));
    setSpecialty(readLine("Специальность: "));
    setCourse(readInt("Курс (1-6): ", 1, 6));
    setGpa(readDouble("Средний балл (0-5): ", 0, 5));
}
void Student::save(ostream &os) const
{
    os << fio << '\n'
       << group << '\n'
       << specialty << '\n'
       << course << '\n'
       << gpa << '\n';
}
void Student::load(istream &is)
{
    setFio(getLineFrom(is));
    setGroup(getLineFrom(is));
    setSpecialty(getLineFrom(is));
    setCourse(parseInt(getLineFrom(is)));
    setGpa(parseDouble(getLineFrom(is)));
}
Base *Student::clone() const { return new Student(*this); }
