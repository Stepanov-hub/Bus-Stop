#pragma once

#include <vector>
#include <string>

struct T {
	std::string company;
	int leave;
	int arrive;
};

class Timetable
{
private:
	std::vector <T> timetable; 
public:
	void add(std::string s, int n); //add data to structure

	Timetable& sort(); //sort the data structure by arrival time

	void task(std::vector <T>& Posh, std::vector <T>& Grotty); //function of the task
};

