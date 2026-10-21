#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

class HRMSException : public exception {
protected:
    string message;
public:
    HRMSException(const string& msg) : message(msg) {}
    virtual const char* what() const noexcept {
        return message.c_str();
    }

    string layNoiDungLoi() const {
        return message;
    }
};

inline string layNoiDungLoi(const exception& loi) {
    return loi.what();
}

class InvalidInputException : public HRMSException {
public:
    InvalidInputException(const string& msg) : HRMSException("Loi nhap lieu: " + msg) {}
};

class DuplicateException : public HRMSException {
public:
    DuplicateException(const string& msg) : HRMSException("Loi trung lap: " + msg) {}
};

class NotFoundException : public HRMSException {
public:
    NotFoundException(const string& msg) : HRMSException("Loi khong tim thay: " + msg) {}
};

class FileException : public HRMSException {
public:
    FileException(const string& msg) : HRMSException("Loi tep du lieu: " + msg) {}
};

class DataFormatException : public HRMSException {
public:
    DataFormatException(const string& msg) : HRMSException("Sai dinh dang du lieu: " + msg) {}
};

#endif // EXCEPTIONS_H
