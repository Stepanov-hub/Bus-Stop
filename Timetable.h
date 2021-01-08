#pragma once

#include <vector>
#include <string>

class Timetable
{
private:
	std::vector <std::pair<std::string,std::pair<int,int>>> timetable;
public:
	void add(std::string s, int n);

	Timetable& sort();

	void task(std::vector <std::pair<std::string, std::pair<int, int>>>& Posh, std::vector <std::pair<std::string, std::pair<int, int>>>& Grotty);
};

