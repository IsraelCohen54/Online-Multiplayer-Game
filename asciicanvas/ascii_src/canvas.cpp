#include "canvas.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>

static const size_t NULLCHAR_SIZE = sizeof('\0');

namespace ascii {

static const CharProxyStrategy &g_legalPositionCharStrategy = LegalBoundsStrategy();
static const CharProxyStrategy &g_outOfBoundsCharStrategy = OutOfBoundsStrategy();

Canvas::CharProxy::CharProxy(const CharProxyStrategy &a_strategy, char *a_buffer, size_t a_idx) 
: m_strategy(a_strategy)
, m_buffer(a_buffer)
, m_idx(a_idx) {
}

Canvas::CharProxy &Canvas::CharProxy::operator=(const CharProxy &a_other) {
    m_strategy.setChar(m_buffer, m_idx, (char)a_other);
    return *this;
}

Canvas::CharProxy::operator char() const {
    return m_strategy.getChar(m_buffer, m_idx);
}

Canvas::CharProxy &Canvas::CharProxy::operator=(const char a_newVal) {
    m_strategy.setChar(m_buffer, m_idx, a_newVal);
    return *this;
}


Canvas::Canvas(size_t a_width, size_t a_height)
: m_width(a_width)
, m_height(a_height)
, m_buffer(SingleLineSize() * a_height, ' ') {
    for (size_t y = 0 ; y < m_height ; ++y) {
        m_buffer[y * SingleLineSize() + m_width] = '\0';
    }
}

void Canvas::Clear() {
    for (size_t y = 0 ; y < m_height ; ++y) {
        std::fill(m_buffer.begin() + (y * SingleLineSize()), m_buffer.begin() + (y * SingleLineSize()) + m_width, ' ');
    }
}

size_t Canvas::SingleLineSize() const {
    return m_width + NULLCHAR_SIZE;
}

Canvas::CharProxy Canvas::operator[](const Point &a_point) {
    return operator()(a_point.GetX(), a_point.GetY());
}

char Canvas::operator[](const Point &a_point) const {
    return const_cast<Canvas *>(this)->operator()(a_point.GetX(), a_point.GetY());
}

Canvas::CharProxy Canvas::operator()(int a_x, int a_y) {
    return CharProxy(
        IsLegalPosition(a_x, a_y) ? g_legalPositionCharStrategy : g_outOfBoundsCharStrategy, 
        m_buffer.data(), a_x + a_y * SingleLineSize());
}

char Canvas::operator()(int a_x, int a_y) const {
    return const_cast<Canvas *>(this)->operator()(a_x, a_y);
}

size_t Canvas::GetWidth() const {
    return m_width;
}

size_t Canvas::GetHeight() const {
    return m_height;
}

bool Canvas::IsLegalPosition(const Point &a_point) const { 
    return IsLegalPosition(a_point.GetX(), a_point.GetY());
}

bool Canvas::IsLegalPosition(int a_x, int a_y) const {
    return (a_x >= 0) && (a_y >= 0) && (a_x < int(m_width)) && (a_y < int(m_height));
}

void Canvas::Print(std::ostream &a_out) const {
    for (size_t y = 0 ; y < m_height ; ++y) {
        a_out << &m_buffer[y * SingleLineSize()] << std::endl;
    }
}

} // ascii
