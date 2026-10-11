#ifndef BASE_H
#define BASE_H
#include <string>
#include <iostream>


// Абстрактный базовый класс сотрудника/студента ВУЗа
class Base {
    protected:
        std::string fio;
    public:
        Base();
        explicit Base(const std::string& fio);
        Base(const Base& other);
        virtual ~Base();

        const std::string& getFio() const;
        void setFio(const std::string& f);

        virtual int type() const = 0;                       // 1 - студент, 2 - преподаватель, 3 - администрация
        virtual const char* typeName() const = 0;
        virtual void print(std::ostream& os) const = 0;     // вывод на экран
        virtual void input() = 0;                           // ввод/изменение с клавиатуры
        virtual void save(std::ostream& os) const = 0;      // запись в файл
        virtual void load(std::istream& is) = 0;            // чтение из файла
        virtual Base* clone() const = 0;                    // копия объекта (для глубокого копирования Keeper)

};

std::ostream& operator<<(std::ostream& os, const Base& b);

#endif
