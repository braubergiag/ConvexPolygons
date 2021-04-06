#pragma once
#include <vector>
#include "Point.h"
class Triangle
{
public:
        std::vector<Point> points;
        std::vector<Point> generatedPoints;
        Point move;
        Triangle(Point a, Point b, Point c);
        Point getPoint(int i) const;
        double getArea();
        void moveToOrigin();
        void moveBack();

};


