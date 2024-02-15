#include "char_proxy_strategies.hpp"

namespace ascii {

void LegalBoundsStrategy::setChar(char *a_buffer, size_t a_idx, char a_newVal) const {
    a_buffer[a_idx] = a_newVal;
}

char LegalBoundsStrategy::getChar(char *a_buffer, size_t a_idx) const {
    return a_buffer[a_idx];
}

void OutOfBoundsStrategy::setChar(char *a_buffer, size_t a_idx, char a_newVal) const {
    // do nothing
}

char OutOfBoundsStrategy::getChar(char *a_buffer, size_t a_idx) const {
    return ' ';
}

} // ascii
