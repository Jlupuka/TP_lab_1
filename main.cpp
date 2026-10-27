#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Admin.h"
#include "Exceptions.h"
#include "Utils.h"
#include <iostream>
using namespace std;

static void menu() {
    cout << "\n===== ВУЗ =====\n"
         << "1. Добавить студента\n2. Добавить преподавателя\n3. Добавить администратора\n"
         << "4. Показать все\n5. Показать одного по номеру\n6. Изменить по номеру\n"
         << "7. Удалить по номеру\n8. Сохранить в файл\n9. Загрузить из файла\n0. Выход\n";
}
static void add(Keeper& k, Base* obj) {
    try { obj->input(); k.add(obj); cout << "Добавлено." << endl; }
    catch (...) { delete obj; throw; }
}
int main() {
    Keeper vuz;
    bool run = true;
    while (run) {
        try {
            menu();
            int c = readInt("Выбор: ", 0, 9);
            switch (c) {
                case 1: add(vuz, new Student()); break;
                case 2: add(vuz, new Teacher()); break;
                case 3: add(vuz, new Admin()); break;
                case 4: cout << vuz; break;
                case 5: { int i = readInt("Номер: ", 1, 1000000); cout << vuz[i - 1] << endl; break; }
                case 6: { int i = readInt("Номер: ", 1, 1000000); cout << vuz[i - 1] << endl; vuz[i - 1].input(); cout << "Изменено." << endl; break; }
                case 7: { int i = readInt("Номер: ", 1, 1000000); vuz.remove(i - 1); cout << "Удалено." << endl; break; }
                case 8: vuz.saveToFile(readLine("Имя файла: ")); cout << "Сохранено." << endl; break;
                case 9: vuz.loadFromFile(readLine("Имя файла: ")); cout << "Загружено." << endl; break;
                case 0: run = false; break;
            }
        } catch (const AppException& e) {
            cout << e.what() << endl;
            if (cin.eof()) break;
        }
    }
    return 0;
}
