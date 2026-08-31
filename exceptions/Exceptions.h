#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class HRMSException : public std::exception {
protected:
    std::string message;
public:
    HRMSException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidInputException : public HRMSException {
public:
    InvalidInputException(const std::string& msg) : HRMSException("Loi nhap lieu: " + msg) {}
};

class DuplicateException : public HRMSException {
public:
    DuplicateException(const std::string& msg) : HRMSException("Loi trung lap: " + msg) {}
};

class NotFoundException : public HRMSException {
public:
    NotFoundException(const std::string& msg) : HRMSException("Loi khong tim thay: " + msg) {}
};

#endif // EXCEPTIONS_H
