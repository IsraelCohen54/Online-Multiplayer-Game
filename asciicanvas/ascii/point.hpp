#ifndef __ASCII_POINT__
#define __ASCII_POINT__

namespace ascii {

class Point {
public:
    Point(int a_x, int a_y);
    Point(const Point &a_other) = default;
    Point& operator=(const Point &a_other) = default;
    ~Point() = default;

    void Set(int a_x, int a_y);
    int GetX() const;
    int GetY() const;

private:
    int m_x;
    int m_y;
};

} // ascii

#endif
