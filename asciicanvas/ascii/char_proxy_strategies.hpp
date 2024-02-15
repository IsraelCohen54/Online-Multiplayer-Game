#ifndef __ASCII_CHAR_PROXY_STRATEGIES__
#define __ASCII_CHAR_PROXY_STRATEGIES__

#include <stddef.h>

namespace ascii {

struct CharProxyStrategy {
    virtual void setChar(char *a_buffer, size_t a_idx, char a_newVal) const = 0;
    virtual char getChar(char *a_buffer, size_t a_idx) const = 0;
};

struct LegalBoundsStrategy : CharProxyStrategy {
    virtual void setChar(char *a_buffer, size_t a_idx, char a_newVal) const;
    virtual char getChar(char *a_buffer, size_t a_idx) const;
};

struct OutOfBoundsStrategy : CharProxyStrategy {
    virtual void setChar(char *a_buffer, size_t a_idx, char a_newVal) const;
    virtual char getChar(char *a_buffer, size_t a_idx) const;
};

} // ascii

#endif
