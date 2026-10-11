#include "Base.h"
#include "Exceptions.h"

using namespace std;

Base::Base() : fio("") { cout << "[Конструктор без параметров] Base" << endl; }
Base::Base(const string& f) : fio(f) { cout << "[Конструктор с параметрами] Base" << endl; }
Base::Base(const Base& o) : fio(o.fio) { cout << "[Конструктор копирования] Base" << endl; }
Base::~Base() { cout << "[Деструктор] Base" << endl; }

const string& Base::getFio() const { return fio; }

void Base::setFio(const string& f) {
    if (f.empty()) throw InputException("ФИО не может быть пустым");
    fio = f;
}
ostream& operator<<(ostream& os, const Base& b) { b.print(os); return os; }
