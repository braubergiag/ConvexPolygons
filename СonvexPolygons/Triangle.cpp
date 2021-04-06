#include "Triangle.h"

    Triangle::Triangle(Point a, Point b, Point c) {
        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
    }
    Point Triangle::getPoint(int i) const {
        if (i >= 0 && i <= 2)
            return points[i];
    }
    double Triangle::getArea() {
        double c1 = sqrt(pow(points[1].m_x - points[0].m_x, 2) + pow(points[1].m_y - points[0].m_y, 2));
        double c2 = sqrt(pow(points[2].m_x - points[1].m_x, 2) + pow(points[2].m_y - points[1].m_y, 2));
        double c3 = sqrt(pow(points[2].m_x - points[0].m_x, 2) + pow(points[2].m_y - points[0].m_y, 2));
        double perimetr = c1 + c2 + c3, p = perimetr / 2;
        return sqrt(p * (p - c1) * (p - c2) * (p - c3));
    }
    void Triangle::moveToOrigin() {
        move.m_x = points[0].m_x;
        move.m_y = points[0].m_y;
        for (int i = 0; i < 3; ++i) {
            points[i].m_x -= move.m_x;
            points[i].m_y -= move.m_y;
        }

    }
    void Triangle::moveBack() {
        for (int i = 0; i < 3; ++i) {
            points[i].m_x += move.m_x;
            points[i].m_y += move.m_y;
        }
    }