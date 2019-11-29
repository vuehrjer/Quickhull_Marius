#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

#include "Point.h"
#include "Quickhull.h"
#include "SDL2-2.0.10/include/SDL.h"

#define WIDTH 640
#define HEIGHT 400

SDL_Window* window;
SDL_bool done;
SDL_Renderer* renderer;
float scale = 4.0f;
std::vector<Point> points;
std::vector<Point> pointsLeft;
std::vector<Point> pointsRight;
std::vector<Point> convexHull;

Point extremLeft;
Point extremRight;
int step = 0;

//is Point(p1) left or right side of line(p2,p3)
float sign(Point p1, Point p2, Point p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

//Distance from line(p2,p3) and point(p1)
float dist(Point p1, Point p2, Point p3)
{
	return fabs((p1.y - p2.y) * (p3.x - p2.x) -
		(p3.y - p2.y) * (p1.x - p2.x));
}

void Update()
{
	switch (step)
	{
	case 0:
		if (extremLeft.x == 0 && extremRight.x == 0)
		{
			extremLeft.x = WIDTH;
			for (Point point : points)
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
		}
		break;
	case 1:
		for (int i = 0; i < points.size(); i++)
		{
			Point point = points[i];
			float det = sign(point, extremLeft, extremRight);
			if (det < 0)
			{
				pointsLeft.push_back(point);
				continue;
			}
			else if (det > 0)
			{
				pointsRight.push_back(point);
				continue;
			}
		}

		break;
	case 2:
		float maxDistance = 0.0f;
		Point maxPoint;
		for (int i = 0; i < pointsLeft.size(); i++)
		{
			Point point = pointsLeft[i];
			float distance = dist(point, extremLeft, extremRight);
			if (distance > maxDistance)
			{
				maxDistance = distance;
				maxPoint = point;
			}
		}
		convexHull.push_back(maxPoint);
		maxDistance = 0.0f;
		for (int i = 0; i < pointsRight.size(); i++)
		{
			Point point = pointsRight[i];
			float distance = dist(point, extremLeft, extremRight);
			if (distance > maxDistance)
			{
				maxDistance = distance;
				maxPoint = point;

			}
		}
		convexHull.push_back(maxPoint);
		iter_swap(convexHull.begin(), convexHull.begin() + convexHull.size()-1);
		break;
	}

	step++;
	if (step == 5) step = 0;
	
}


void Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	SDL_RenderSetScale(renderer, scale, scale);
	for (auto point : points)
	{
		SDL_RenderDrawPointF(renderer, point.x / scale, point.y / scale);
	}

	for (int i = 0; i < convexHull.size(); i++)
	{
		int begin = i;
		int end = i + 1;
		if (end == convexHull.size()) end = 0;
		Point p1 = convexHull[begin];
		Point p2 = convexHull[end];
		SDL_RenderDrawLineF(renderer, p1.x/scale, p1.y / scale, p2.x / scale, p2.y / scale);

	}
	//SDL_RenderDrawLineF(renderer, extremLeft.x / scale, extremLeft.y / scale, extremRight.x / scale, extremRight.y / scale);


	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	for (Point point : pointsLeft)
	{
		SDL_RenderDrawPointF(renderer, point.x / scale, point.y / scale);

	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	for (Point point : pointsRight)
	{
		SDL_RenderDrawPointF(renderer, point.x / scale, point.y / scale);

	}

	SDL_RenderPresent(renderer);
}

void OnEvent(SDL_Event* event)
{
	if (event->type == SDL_QUIT)
	{
		done = SDL_TRUE;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
		{
			done = SDL_TRUE;
		}
		else if (event->key.keysym.sym == SDLK_SPACE)
		{
			Update();
		}
	}
}

int main(int argc, char* argv[])
{
	std::string line;
	std::ifstream myfile;
	myfile.open("randomFloats.txt");

	if (myfile.is_open())
	{
		std::getline(myfile, line);
		int numberCount = std::stoi(line);


		while (std::getline(myfile, line))
		{
			float x = std::stof(line.substr(0, line.find(','))) * WIDTH;
			float y = std::stof(line.substr(line.find(',') + 1, line.length())) * HEIGHT;


			points.push_back(Point(x, y));
		}

	}

	Quickhull ch(points);
	convexHull = ch.GetHull();
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		window = NULL;
		renderer = NULL;

		if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) == 0) {
			//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			done = SDL_FALSE;

			//main Loop
			while (!done) {
				SDL_Event event;
				Render();

				while (SDL_PollEvent(&event)) {
					OnEvent(&event);
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
	return 0;
}


