#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "Clock.h"
#include "Point.h"
#include "Quickhull.h"
#include "SDL2-2.0.10/include/SDL.h"


#define WIDTH 3000
#define HEIGHT 5000

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
bool render;

Point extremLeft;
Point extremRight;
int step = 0;


void Update()
{
	/*std::string line;
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

	}*/
	Quickhull qh(points, render);
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
	for(int j = 0; j < step; j++)
	{ 
		for (int i = 0; i < allTheHulls[j].size(); i++)
		{
			int begin = i;
			int end = i + 1;
			if (end == allTheHulls[j].size()) end = 0;


			for (int i = 0; i < points.size() - 1; i++)
			{
				Point p1 = allTheHulls[j][begin];
				Point p2 = allTheHulls[j][end];

				SDL_RenderDrawLineF(renderer, p1.x / scale, p1.y / scale, p2.x / scale, p2.y / scale);
			}
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

	render = false;
	/*std::string line;
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
	*/
	std::vector<float> xValues;
	std::vector<float> yValues;
	srand(0);
	for (int i = 0; i < 1000000; i++)
	{
		float x = (float)rand() / RAND_MAX * WIDTH + 50;
		xValues.push_back(x);
	}

	for (int i = 0; i < 1000000; i++)
	{
		float y = (float)rand() / RAND_MAX * HEIGHT + 100;
		yValues.push_back(y);
	}
	if (xValues.size() == yValues.size()) {
		for (int i = 0; i < xValues.size(); i++)
		{
			points.push_back(Point(xValues[i], yValues[i]));
		}

	}
	else
	{
		std::cout << "x and y Values are unequal" << std::endl;
		return -1;
	}
	
	Clock clock;
	std::chrono::high_resolution_clock::time_point start = clock.getStartTime();
	Quickhull ch(points, render);
	std::chrono::high_resolution_clock::time_point end = clock.getEndTime();
	clock.printTime(start, end);
	convexHull = ch.GetHull();
	if (render)
	{
		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			window = NULL;
			renderer = NULL;

			if (SDL_CreateWindowAndRenderer(750, 700, 0, &window, &renderer) == 0) {
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
}


