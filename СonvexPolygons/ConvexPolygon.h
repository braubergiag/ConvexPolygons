#pragma once
#include <vector>
#include "Triangle.h"
#include "Point.h"
#include <Eigen/Dense>
#include <map>
#include <random>
#include <chrono>
#include <iostream>
using namespace Eigen;
using namespace std;
class ConvexPolygon
{
public:
    unsigned int n;
    unsigned long int m_iterations;
    double area, max_width, max_height;
    vector<Point> points;
    vector<Triangle> triangles;
    vector<Point> generatedPoints;
    vector<double> trianglesAreas;
    vector<double> probabilities;
    std::map<int, int> distrib;
    ConvexPolygon(unsigned int n_vertices,double mWidth = 1, double mHeight = 1) : 
        n(n_vertices), max_width(mWidth),max_height(mHeight)
    {
        generateConvexPolygon();
        
    }
    void generateConvexPolygon();
    void trianglateConvexPolygon();
    void calculateTrianglesAreas();
    void calculateProbabilities();
    void generateDiscreteDistrib(unsigned int iterations);
    void generatePointsInTriangle();
};

