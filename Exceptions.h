#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>

// Базовое исключение приложения: хранит поясняющий текст
class AppException : public std::exception {
    protected:
        std::string msg;
    public:
        explicit AppException(const std::string& m) : msg(m) {}
        virtual ~AppException() throw() {}
        const char* what() const throw() { return msg.c_str(); }
};

class InputException : public AppException {
    public: explicit InputException(const std::string& m) : AppException("Ошибка ввода: " + m) {}
};
class IndexException : public AppException {
    public: explicit IndexException(const std::string& m) : AppException("Ошибка индекса: " + m) {}
};
class FileException : public AppException {
    public: explicit FileException(const std::string& m) : AppException("Ошибка файла: " + m) {}
};
class FormatException : public AppException {   
    public: explicit FormatException(const std::string& m) : AppException("Ошибка формата данных: " + m) {}
};

#endif
