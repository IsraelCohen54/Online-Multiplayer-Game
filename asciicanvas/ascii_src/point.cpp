#include "point.hpp"

namespace ascii {

Point::Point(int a_x, int a_y)
: m_x(a_x)
, m_y(a_y) {

}

void Point::Set(int a_x, int a_y) {
    m_x = a_x;
    m_y = a_y;
}

int Point::GetX() const {
    return m_x;
}

int Point::GetY() const {
    return m_y;
}

} // ascii
