#pragma once
#include <vector>
#include "Point.h"

class Quickhull
{
public:
	Quickhull(std::vector<Point> p, bool render);
	std::vector<Point> findExtremes(std::vector<Point> p);
	std::vector<std::vector<Point> >getAllHulls();
	std::vector<Point> GetHull();
private:
	std::vector<std::vector<Point> > allHulls;
	void FindHull(std::vector<Point>& p, const Point& a, const Point& b, bool render);
	std::vector<Point> convexHull;
	float sign(Point p1, Point p2, Point p3);
	float dist(Point p1, Point p2, Point p3);
	bool pointInTriangle(Point pt, Point v1, Point v2, Point v3);

};

