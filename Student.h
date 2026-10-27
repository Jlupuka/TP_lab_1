#ifndef STUDENT_H
#define STUDENT_H
#include "Base.h"

class Student : public Base {
    std::string group, specialty;
    int course;
    double gpa;
public:
    Student();
    Student(const std::string& fio, const std::string& group, const std::string& specialty, int course, double gpa);
    Student(const Student& o);
    ~Student();
    Student& operator=(const Student& o);
    bool operator==(const Student& o) const;

    const std::string& getGroup() const;     void setGroup(const std::string& g);
    const std::string& getSpecialty() const; void setSpecialty(const std::string& s);
    int getCourse() const;                   void setCourse(int c);
    double getGpa() const;                   void setGpa(double g);

    int type() const;
    const char* typeName() const;
    void print(std::ostream& os) const;
    void input();
    void save(std::ostream& os) const;
    void load(std::istream& is);
    Base* clone() const;
};
#endif
