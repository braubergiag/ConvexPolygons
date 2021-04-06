// СonvexPolygons.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <fstream>
#include <vector>

#include <algorithm>
#include <cmath>

#include "ConvexPolygon.h"
using namespace std;

int main()
{
    long int iterations = 10e4;
    const int n = 10;

    ConvexPolygon polygon(n,1000,1000);
    polygon.trianglateConvexPolygon();
    polygon.calculateTrianglesAreas();
    polygon.calculateProbabilities();
    polygon.generateDiscreteDistrib(iterations);
    polygon.generatePointsInTriangle();

    ofstream out1,out2,out3;

    // Отрисовка многоугольника
    out1.open("polygonPoints.dat");
    out1 << "# x" << " " << "y" << endl;

    for (int i = 0; i < polygon.points.size(); ++i)
        out1 << polygon.points[i].m_x << " " << polygon.points[i].m_y << endl;
    out1 << polygon.points[0].m_x << " " << polygon.points[0].m_y;


    // Отрисовка треугольников
    out2.open("polygon.dat");
    out2 << "# x" << " " << "y" << endl;
    for (int i = 0; i < polygon.triangles.size(); ++i) {
        for (int j = 0; j < 3; ++j)
            out2 << polygon.triangles[i].getPoint(j).getX() << " " << polygon.triangles[i].getPoint(j).getY() << endl;
        out2 << polygon.triangles[i].getPoint(0).getX() << " " << polygon.triangles[i].getPoint(0).getY() << endl;

    }

    // Отрисовка точек
    out3.open("points.dat");
    out3 << "# x" << " " << "y" << endl;
    for (int i = 0; i < polygon.generatedPoints.size(); ++i)
        out3 << polygon.generatedPoints[i].m_x << " " << polygon.generatedPoints[i].m_y << endl;
        



}
