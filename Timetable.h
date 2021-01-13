#pragma once

#include <vector>
#include <string>

class Timetable
{
private:
	std::vector <std::pair<std::string,std::pair<int,int>>> timetable; // в парах хранится название компании и время, где время представлено в виде ещё одной пары(first отправление и second приезд)
public:
	void add(std::string s, int n); //функия добавления в структуру данных

	Timetable& sort(); //сортировка структуры данных по времени прибытия

	void task(std::vector <std::pair<std::string, std::pair<int, int>>>& Posh, std::vector <std::pair<std::string, std::pair<int, int>>>& Grotty); //функция самого задания
};

