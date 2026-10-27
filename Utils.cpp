#include "Utils.h"
#include "Exceptions.h"
#include <iostream>
#include <cstdlib>

using namespace std;

string getLineFrom(istream &in)
{
    string s;
    if (!getline(in, s))
        throw FormatException("неожиданный конец данных");
    if (!s.empty() && s[s.size() - 1] == 'r')
        s.erase(s.size() - 1);
    return s;
}

int parseInt(const string &s)
{
    char *end = 0;
    long v = strtol(s.c_str(), &end, 10);

    if (s.empty() || *end != '\0')
        throw InputException("'" + s + "' не является целым числом");
    return (int)v;
}
double parseDouble(const string &s)
{
    char *end = 0;
    string t = s;
    for (size_t i = 0; i < t.size(); ++i)
        if (t[i] == ',')
            t[i] = '.';
    double v = strtod(t.c_str(), &end);
    if (t.empty() || *end != '\0')
        throw InputException("'" + s + "' не является числом");
    return v;
}
string readLine(const string &prompt)
{
    cout << prompt;
    string s;
    if (!getline(cin, s))
        throw InputException("поток ввода закрыт");
    if (!s.empty() && s[s.size() - 1] == '\r')
        s.erase(s.size() - 1);
    if (s.empty())
        throw InputException("пустая строка недопустима");
    return s;
}
int readInt(const string &prompt, int min, int max)
{
    int v = parseInt(readLine(prompt));
    if (v < min || v > max)
        throw InputException("значение должно быть от " + to_string(min) + " до " + to_string(max));
    return v;
}
double readDouble(const string &prompt, double min, double max)
{
    double v = parseDouble(readLine(prompt));
    if (v < min || v > max)
        throw InputException("значение вне допустимого диапазона");
    return v;
}