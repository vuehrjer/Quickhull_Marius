#include "Quickhull.h"
#include <iostream>

Quickhull::Quickhull(std::vector<Point> p)
{
	std::vector<Point> extremes;
	Point extremLeft(640, 0);
	Point extremRight(0,0);
	for (Point point : p)
	{
		if (point.x < extremLeft.x)
		{
			extremLeft.x = point.x;
			extremLeft.y = point.y;
		}
		else if (point.x > extremRight.x)
		{
			extremRight.x = point.x;
			extremRight.y = point.y;
		}
	}

	std::vector<Point> pointsLeft;
	std::vector<Point> pointsRight;
	for (auto point : p)
	{
		
		float det = sign(extremLeft, extremRight, point);
		if (det > 0)
		{
			pointsLeft.push_back(point);
		}
		else if (det < 0)
		{
			pointsRight.push_back(point);
		}
		else continue;

	}
	extremes.push_back(extremLeft);
	extremes.push_back(extremRight);
	allHulls.push_back(extremes);


	convexHull.push_back(extremLeft);

	FindHull(pointsLeft, extremLeft, extremRight);

	convexHull.push_back(extremRight);

	FindHull(pointsRight, extremRight, extremLeft);
}

void Quickhull::FindHull(std::vector<Point>& p, const Point& a, const Point& b)
{

	std::vector<Point> tempHull;
	if (p.empty()) return;
	float maxDistance = 0.0f;
	Point maxPoint;
	for (Point point : p)
	{
		float distance = dist(a, b, point);
		if (distance > maxDistance)
		{
			maxDistance = distance;
			maxPoint = point;
		}
	}
	std::vector<Point> left;

	for (auto pt : p)
	{
		if (sign(a, maxPoint, pt) > 0)
		{
			left.push_back(pt);
		}
	}
	Point extremLeft(640, 0);
	Point extremRight(0, 0);
	for (Point point : p)
	{
		if (point.x < extremLeft.x)
		{
			extremLeft.x = point.x;
			extremLeft.y = point.y;
		}
		else if (point.x > extremRight.x)
		{
			extremRight.x = point.x;
			extremRight.y = point.y;
		}
	}

	FindHull(left, a, maxPoint);

	convexHull.push_back(maxPoint);

	//tempHull = convexHull;

	//tempHull.push_back(extremRight);

	allHulls.push_back(convexHull);

	std::vector<Point> right;

	for (auto pt : p)
	{
		if (sign(maxPoint, b, pt) > 0)
		{
			right.push_back(pt);
		}
	}
	
	for (int i = 0; i < p.size(); i++)
	{
		if (pointInTriangle(p[i], a, maxPoint, b)) { p.erase(p.begin() + i); }
	}
	std::vector<Point> pointsLeft;
	std::vector<Point> pointsRight;
	for (int i = 0; i < p.size(); i++)
	{
		Point point = p[i];
		float det = sign(point, a, b);
		if (det < 0)
		{
			pointsLeft.push_back(point);
		}
		else if (det > 0)
		{
			pointsRight.push_back(point);
		}
	}
	
	//remove points inside

	FindHull(right, maxPoint, b);

}

std::vector<Point> Quickhull::GetHull()
{
	return convexHull;
}

float Quickhull::sign(Point p1, Point p2, Point p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

float Quickhull::dist(Point p1, Point p2, Point p3)
{
	return fabs ((p1.y - p3.y) * (p2.x - p1.x) -
				(p2.y - p1.y) * (p1.x - p3.x));
}

bool Quickhull::pointInTriangle(Point pt, Point v1, Point v2, Point v3)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(pt, v1, v2);
	d2 = sign(pt, v2, v3);
	d3 = sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}


std::vector<Point> Quickhull::findExtremes(std::vector<Point> p)
{
	std::vector<Point> extrem;
	Point extremLeft(640, 0);
	Point extremRight(0, 0);
	for (Point point : p)
	{
		if (point.x < extremLeft.x)
		{
			extremLeft.x = point.x;
			extremLeft.y = point.y;
		}
		else if (point.x > extremRight.x)
		{
			extremRight.x = point.x;
			extremRight.y = point.y;
		}
	}
	extrem.push_back(extremLeft);
	extrem.push_back(extremRight);
	
	return extrem;
}

std::vector<std::vector<Point> > Quickhull::getAllHulls()
{
	return allHulls;
}
