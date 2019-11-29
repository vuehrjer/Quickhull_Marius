#include "Quickhull.h"

Quickhull::Quickhull(std::vector<Point> p)
{
	Point extremLeft(640, 0);
	Point extremRight(0,0);
	for (Point point : p)
	{
		if (point.x < extremLeft.x)
		{
			extremLeft.x = point.x;
			extremLeft.y = point.y;
		}
		if (point.x > extremRight.x)
		{
			extremRight.x = point.x;
			extremRight.y = point.y;
		}
	}
	convexHull.push_back(extremLeft);
	convexHull.push_back(extremRight);


	std::vector<Point> pointsLeft;
	std::vector<Point> pointsRight;
	for (int i = 0; i < p.size(); i++)
	{
		Point point = p[i];
		float det = sign(point, extremLeft, extremRight);
		if (det < 0)
		{
			pointsLeft.push_back(point);
		}
		else if (det > 0)
		{
			pointsRight.push_back(point);
		}
	}

	FindHull(pointsLeft, extremLeft, extremRight);
	FindHull(pointsRight, extremRight, extremLeft);
}

void Quickhull::FindHull(std::vector<Point> p, Point a, Point b)
{
	if (p.empty()) return;
	float maxDistance = 0.0f;
	Point maxPoint;
	for (int i = 0; i < p.size(); i++)
	{
		Point point = p[i];
		float distance = dist(point, a, b);
		if (distance > maxDistance)
		{
			maxDistance = distance;
			maxPoint = point;
		}
	}
	convexHull.push_back(maxPoint);

	for (int i = 0; i < p.size(); i++)
	{
		if (pointInTriangle(p[i], a, maxPoint, b)) p.erase(p.begin() + i);
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
	FindHull(pointsLeft, a, maxPoint);
	FindHull(pointsRight, maxPoint, b);
}

std::vector<Point> Quickhull::GetHull()
{
	return convexHull;
}

float Quickhull::sign(Point p1, Point p2, Point p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

float Quickhull::dist(Point p1, Point p2, Point p3)
{
	return fabs ((p1.y - p2.y) * (p3.x - p2.x) -
				(p3.y - p2.y) * (p1.x - p2.x));
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


