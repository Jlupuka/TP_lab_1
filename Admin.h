#ifndef ADMIN_H
#define ADMIN_H
#include "Base.h"

class Admin : public Base {
    std::string position, phone, area;
    public:
        Admin();
        Admin(
            const std::string& fio, 
            const std::string& position,
            const std::string& phone,
            const std::string& area
        );
        Admin(const Admin& o);
        ~Admin();
        Admin& operator=(const Admin& o);
        bool operator==(const Admin& o) const;

        const std::string& getPosition() const; void setPosition(const std::string& p);
        const std::string& getPhone() const;    void setPhone(const std::string& p);
        const std::string& getArea() const;     void setArea(const std::string& a);

        int type() const;
        const char* typeName() const;
        void print(std::ostream& os) const;
        void input();
        void save(std::ostream& os) const;
        void load(std::istream& is);
        Base* clone() const;

};

#endif
