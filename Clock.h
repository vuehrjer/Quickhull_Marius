#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>


class Clock {

public:
	Clock();
	std::string formatTime(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end);
	std::chrono::high_resolution_clock::time_point getStartTime();
	std::chrono::high_resolution_clock::time_point getEndTime();
	void printTime(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end);
private:


};
