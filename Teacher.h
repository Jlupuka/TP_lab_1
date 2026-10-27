#ifndef TEACHER_H
#define TEACHER_H
#include "Base.h"

class Teacher : public Base
{
    std::string *groups;
    int groupCount; // динамический массив групп
    std::string *subjects;
    int subjectCount; // динамический массив предметов
    static std::string *copyArr(const std::string *src, int n);

public:
    Teacher();
    Teacher(const std::string &fio, const std::string *groups, int gc, const std::string *subjects, int sc);
    Teacher(const Teacher &o);
    ~Teacher();
    Teacher &operator=(const Teacher &o);
    bool operator==(const Teacher &o) const;

    int getGroupCount() const;
    const std::string &getGroup(int i) const;
    int getSubjectCount() const;
    const std::string &getSubject(int i) const;
    void setGroups(const std::string *g, int n);
    void setSubjects(const std::string *s, int n);
    void addGroup(const std::string &g);
    void addSubject(const std::string &s);

    int type() const;
    const char *typeName() const;
    void print(std::ostream &os) const;
    void input();
    void save(std::ostream &os) const;
    void load(std::istream &is);
    Base *clone() const;
};
#endif
