#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <istream>

std::string readLine(const std::string &prompt);          // ввод строки с клавиатуры
int readInt(const std::string &prompt, int min, int max); // ввод целого в диапазоне
double readDouble(const std::string &prompt, double min, double max);

std::string getLineFrom(std::istream &in); // чтение строки из файла
int parseInt(const std::string &s);
double parseDouble(const std::string &s);

#endif
