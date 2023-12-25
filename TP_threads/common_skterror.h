#ifndef COMMON_SKT_ERROR_H
#define COMMON_SKT_ERROR_H

#include <exception>

class SktError : public std::exception {
    char msg_error[256];

    public:
    SktError(int error_code, const char* fmt, ...) noexcept;

    virtual const char* what() const noexcept;

    virtual ~SktError();
};

#endif
