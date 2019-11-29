#pragma once
#include <vector>
#include "Point.h"

class Quickhull
{
public:
	Quickhull(std::vector<Point> p);
	
	std::vector<Point> GetHull();
private:

	void FindHull(std::vector<Point> p, Point a, Point b);

	std::vector<Point> convexHull;
	float sign(Point p1, Point p2, Point p3);
	float dist(Point p1, Point p2, Point p3);
	bool pointInTriangle(Point pt, Point v1, Point v2, Point v3);
};

