#include "Teacher.h"
#include "Exceptions.h"
#include "Utils.h"
using namespace std;

string *Teacher::copyArr(const string *src, int n)
{
    if (n <= 0)
        return 0;
    string *a = new string[n];
    for (int i = 0; i < n; ++i)
        a[i] = src[i];
    return a;
}
Teacher::Teacher() : Base(), groups(0), groupCount(0), subjects(0), subjectCount(0)
{
    cout << "[Конструктор без параметров] Teacher" << endl;
}
Teacher::Teacher(const string &f, const string *g, int gc, const string *s, int sc)
    : Base(f), groups(0), groupCount(0), subjects(0), subjectCount(0)
{
    setGroups(g, gc);
    setSubjects(s, sc);
    cout << "[Конструктор с параметрами] Teacher" << endl;
}
Teacher::Teacher(const Teacher &o) : Base(o), groups(copyArr(o.groups, o.groupCount)), groupCount(o.groupCount),
                                     subjects(copyArr(o.subjects, o.subjectCount)), subjectCount(o.subjectCount)
{
    cout << "[Конструктор копирования] Teacher" << endl;
}
Teacher::~Teacher()
{
    delete[] groups;
    delete[] subjects;
    cout << "[Деструктор] Teacher" << endl;
}
Teacher &Teacher::operator=(const Teacher &o)
{
    if (this != &o)
    {
        string *g = copyArr(o.groups, o.groupCount);
        string *s = copyArr(o.subjects, o.subjectCount);
        delete[] groups;
        delete[] subjects;
        fio = o.fio;
        groups = g;
        groupCount = o.groupCount;
        subjects = s;
        subjectCount = o.subjectCount;
    }
    return *this;
}
bool Teacher::operator==(const Teacher &o) const
{
    if (fio != o.fio || groupCount != o.groupCount || subjectCount != o.subjectCount)
        return false;
    for (int i = 0; i < groupCount; ++i)
        if (groups[i] != o.groups[i])
            return false;
    for (int i = 0; i < subjectCount; ++i)
        if (subjects[i] != o.subjects[i])
            return false;
    return true;
}

int Teacher::getGroupCount() const { return groupCount; }
const string &Teacher::getGroup(int i) const
{
    if (i < 0 || i >= groupCount)
        throw IndexException("нет группы с номером " + to_string(i));
    return groups[i];
}
int Teacher::getSubjectCount() const { return subjectCount; }
const string &Teacher::getSubject(int i) const
{
    if (i < 0 || i >= subjectCount)
        throw IndexException("нет предмета с номером " + to_string(i));
    return subjects[i];
}
void Teacher::setGroups(const string *g, int n)
{
    if (n < 0)
        throw InputException("количество групп не может быть отрицательным");
    string *a = copyArr(g, n);
    delete[] groups;
    groups = a;
    groupCount = n;
}
void Teacher::setSubjects(const string *s, int n)
{
    if (n < 0)
        throw InputException("количество предметов не может быть отрицательным");
    string *a = copyArr(s, n);
    delete[] subjects;
    subjects = a;
    subjectCount = n;
}
void Teacher::addGroup(const string &g)
{
    if (g.empty())
        throw InputException("группа не может быть пустой");
    string *a = new string[groupCount + 1];
    for (int i = 0; i < groupCount; ++i)
        a[i] = groups[i];
    a[groupCount] = g;
    delete[] groups;
    groups = a;
    ++groupCount;
}
void Teacher::addSubject(const string &s)
{
    if (s.empty())
        throw InputException("предмет не может быть пустым");
    string *a = new string[subjectCount + 1];
    for (int i = 0; i < subjectCount; ++i)
        a[i] = subjects[i];
    a[subjectCount] = s;
    delete[] subjects;
    subjects = a;
    ++subjectCount;
}

int Teacher::type() const { return 2; }
const char *Teacher::typeName() const { return "Преподаватель"; }
void Teacher::print(ostream &os) const
{
    os << "Преподаватель: " << fio << "; группы: ";
    for (int i = 0; i < groupCount; ++i)
        os << (i ? ", " : "") << groups[i];
    os << "; предметы: ";
    for (int i = 0; i < subjectCount; ++i)
        os << (i ? ", " : "") << subjects[i];
}
void Teacher::input()
{
    setFio(readLine("ФИО: "));
    setGroups(0, 0);
    setSubjects(0, 0);
    int n = readInt("Сколько групп ведёт (0-50): ", 0, 50);
    for (int i = 0; i < n; ++i)
        addGroup(readLine("  Группа " + to_string(i + 1) + ": "));
    n = readInt("Сколько предметов преподаёт (0-50): ", 0, 50);
    for (int i = 0; i < n; ++i)
        addSubject(readLine("  Предмет " + to_string(i + 1) + ": "));
}
void Teacher::save(ostream &os) const
{
    os << fio << '\n'
       << groupCount << '\n';
    for (int i = 0; i < groupCount; ++i)
        os << groups[i] << '\n';
    os << subjectCount << '\n';
    for (int i = 0; i < subjectCount; ++i)
        os << subjects[i] << '\n';
}
void Teacher::load(istream &is)
{
    setFio(getLineFrom(is));
    setGroups(0, 0);
    setSubjects(0, 0);
    int n = parseInt(getLineFrom(is));
    if (n < 0 || n > 1000)
        throw FormatException("некорректное количество групп");
    for (int i = 0; i < n; ++i)
        addGroup(getLineFrom(is));
    n = parseInt(getLineFrom(is));
    if (n < 0 || n > 1000)
        throw FormatException("некорректное количество предметов");
    for (int i = 0; i < n; ++i)
        addSubject(getLineFrom(is));
}
Base *Teacher::clone() const { return new Teacher(*this); }
