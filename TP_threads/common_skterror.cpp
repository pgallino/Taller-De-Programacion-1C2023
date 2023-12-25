#undef _GNU_SOURCE
#undef GNU_SOURCE

#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <cstring>

#include "common_skterror.h"

SktError::SktError(int error_code, const char* fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);

    int s = vsnprintf(msg_error, sizeof(msg_error), fmt, args);

    va_end(args);

    if (s < 0) {
        msg_error[0] = msg_error[1] = msg_error[2] = '?';
        msg_error[3] = ' ';
        msg_error[4] = '\0';

        s = 4;
    } else if (s == sizeof(msg_error)) {
    }
    strerror_r(error_code, msg_error+s, sizeof(msg_error)-s);
    msg_error[sizeof(msg_error)-1] = 0;
}

const char* SktError::what() const noexcept {
    return msg_error;
}

SktError::~SktError() {}
