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
std::vector<Point> temporaryHull;
std::vector<std::vector<Point> > allTheHulls;

Point extremLeft;
Point extremRight;
int step = 0;


void Update()
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
	Quickhull qh(points);
	allTheHulls = qh.getAllHulls();
	temporaryHull = allTheHulls[step];
	
	if(step < allTheHulls.size() -1) step++;
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

	for (int i = 0; i < temporaryHull.size(); i++)
	{
		int begin = i;
		int end = i + 1;
		if (end == temporaryHull.size()) end = 0;

		for (int i = 0; i < points.size() -1; i++)
		{
			Point p1 = temporaryHull[begin];
			Point p2 = temporaryHull[end];

			SDL_RenderDrawLineF(renderer, p1.x / scale, p1.y / scale, p2.x / scale, p2.y / scale);
		}

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


