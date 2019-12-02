#include "Clock.h"

Clock::Clock() {}

std::string Clock::formatTime(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end)
{
	std::chrono::high_resolution_clock::duration time = end - start;
	std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(time);
	time -= h;
	std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes>(time);
	time -= m;
	std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(time);
	time -= s;
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(time);
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << h.count() << ":" << std::setw(2) << m.count() << ":" << std::setw(2) << s.count() << "." << std::setw(3) << ms.count();
	return ss.str();
}

std::chrono::high_resolution_clock::time_point Clock::getStartTime() {
	std::chrono::high_resolution_clock::time_point start;
	start = std::chrono::high_resolution_clock::now();
	return start;
}

std::chrono::high_resolution_clock::time_point Clock::getEndTime() {
	std::chrono::high_resolution_clock::time_point end;
	end = std::chrono::high_resolution_clock::now();
	return end;
}

void Clock::printTime(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end) {
	std::cout << formatTime(start, end) << std::endl;
}