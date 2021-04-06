#include "ConvexPolygon.h"




void ConvexPolygon::generateConvexPolygon() {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 generator(seed);
        uniform_real_distribution<double> dist(0.0, 1.0);
        uniform_real_distribution<double> distX(0.0, max_width);
        uniform_real_distribution<double> distY(0.0, max_height);


        vector<double> xPool;
        vector<double> yPool;

        for (int i = 0; i < n; ++i) {
            xPool.push_back(distX(generator));
            yPool.push_back(distY(generator));
        }
        sort(xPool.begin(), xPool.end());
        sort(yPool.begin(), yPool.end());

        double minX = xPool[0];
        double maxX = xPool[n - 1];
        double minY = yPool[0];
        double maxY = yPool[n - 1];

        vector<double> xVec;
        vector<double> yVec;

        double lastTop = minX, lastBot = minX;

        for (int i = 1; i < n - 1; i++) {
            double x = xPool[i];

            if (dist(generator) > 0.5) {
                xVec.push_back(x - lastTop);
                lastTop = x;
            }
            else {
                xVec.push_back(lastBot - x);
                lastBot = x;
            }
        }

        xVec.push_back(maxX - lastTop);
        xVec.push_back(lastBot - maxX);

        double lastLeft = minY, lastRight = minY;
        for (int i = 1; i < n - 1; ++i) {
            double y = yPool[i];
            if (dist(generator) > 0.5) {
                yVec.push_back(y - lastLeft);
                lastLeft = y;
            }
            else {
                yVec.push_back(lastRight - y);
                lastRight = y;
            }
        }
        yVec.push_back(maxY - lastLeft);
        yVec.push_back(lastRight - maxY);

        std::shuffle(yVec.begin(), yVec.end(), generator);

        vector<Point> vec;
        for (int i = 0; i < n; ++i) {
            vec.push_back(Point(xVec[i], yVec[i]));
        }
        sort(vec.begin(), vec.end(), sortPoints());

        double x = 0, y = 0;
        double minPolygonX = 0;
        double minPolygonY = 0;


        for (int i = 0; i < n; ++i) {
            points.push_back(Point(x, y));
            x += vec[i].getX();
            y += vec[i].getY();

            minPolygonX = min(minPolygonX, x);
            minPolygonY = min(minPolygonY, y);
        }
        double xShift = minX - minPolygonX;
        double yShift = minY - minPolygonY;

        for (int i = 0; i < n; ++i) {
            Point p = points[i];
            points[i] = Point(p.getX() + xShift, p.getY() + yShift);
        }
    }
void ConvexPolygon::trianglateConvexPolygon() {
        for (int i = 0, j = 1, k = 2; k <= points.size() - 1; j += 1, k += 1) {
            Triangle t(points[i], points[j], points[k]);
            triangles.push_back(t);
        }
    }
void ConvexPolygon::calculateTrianglesAreas() {
        for (int i = 0; i < triangles.size(); ++i) {
            double triangleArea = triangles[i].getArea();
            trianglesAreas.push_back(triangleArea);
            area += triangleArea;
        }

    }
void ConvexPolygon::calculateProbabilities() {
        for (int i = 0; i < triangles.size(); ++i)
            probabilities.push_back(trianglesAreas[i] / area);
    }
void ConvexPolygon::generateDiscreteDistrib(unsigned int iterations) {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> d(probabilities.begin(), probabilities.end());
        m_iterations = iterations;
        for (int n = 0; n < m_iterations; ++n) {
            ++distrib[d(gen)];
        }
        for (auto p : distrib) {
            std::cout << p.first << " generated " << p.second << " times\n";
        }
    }
void ConvexPolygon:: generatePointsInTriangle() {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 generator(seed);
        uniform_real_distribution<double> dist(0.0, 1.0);
        unsigned long int currIter = 0;
        for (int i = 0; i < triangles.size() && currIter < m_iterations; ++i) {
            Matrix2d mat;
            triangles[i].moveToOrigin();
            mat << triangles[i].getPoint(1).getX(), triangles[i].getPoint(2).getX(),
                triangles[i].getPoint(1).getY(), triangles[i].getPoint(2).getY();
            Vector2d unif_vec;
            unif_vec << dist(generator), dist(generator);
            
            for (int j = 0; j < distrib[i]; ++j, ++currIter) {

                unif_vec << dist(generator), dist(generator);
                if (unif_vec.sum() > 1) {
                    unif_vec(0) = 1 - unif_vec(0);
                    unif_vec(1) = 1 - unif_vec(1);
                }
                Point p((mat * unif_vec)(0), (mat * unif_vec)(1));
                p.m_x += triangles[i].move.m_x;
                p.m_y += triangles[i].move.m_y;
                generatedPoints.push_back(p);


            }
            triangles[i].moveBack();


        }
    }

