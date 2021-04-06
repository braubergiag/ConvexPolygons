#pragma once
struct Point {
    Point(double x, double y) : m_x(x), m_y(y) {};
    Point() :m_x(0.0), m_y(0.0) {};
    double m_x;
    double m_y;
    double getX() const { return m_x; }
    double getY() const { return m_y; }
};
struct sortPoints {
    inline bool operator()(const Point& a, const Point& b) {
        return atan2(a.getX(), a.getY()) < atan2(b.getX(), b.getY());
    }
};