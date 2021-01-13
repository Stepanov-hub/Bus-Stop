#pragma once

#include <vector>
#include <string>

struct schedule {
	std::string company;
	int leave;
	int arrive;
};

class Timetable
{
private:
	std::vector <schedule> timetable; 
public:
	void add(std::string s, int n); //add data to structure

	Timetable& sort(); //sort the data structure by arrival time

	void task(std::vector <schedule>& Posh, std::vector <schedule>& Grotty); //function of the task
};

