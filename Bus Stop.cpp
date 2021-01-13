#include <iostream>
#include <fstream>

#include "Timetable.h"

void print(std::vector <std::pair<std::string, std::pair<int, int>>>& company, std::ofstream& outf);

std::string convert(int k);

int main() {
	std::ifstream inf("input.txt");
	std::ofstream outf("output.txt");

	Timetable general;

	std::vector <std::pair<std::string, std::pair<int, int>>> Posh;
	std::vector <std::pair<std::string, std::pair<int, int>>> Grotty;

	int n = 0;

	while (inf) { //добавление данных из файла в структуру данных
		std::string input;
		inf >> input;
		if (input == "")
			break;
		general.add(input, n);
		if (n == 2)
			n = 0;
		else
			++n;
	}

	general.sort().task(Posh, Grotty); //сортировка и выполнение задания

	print(Posh, outf);
	if(Posh.size()!=0)
		outf << '\n';
	print(Grotty, outf);

	return 0;
}

void print(std::vector <std::pair<std::string, std::pair<int, int>>>& company, std::ofstream& outf) { //функция записи данных в выходной файл
	for (int i = 0; i < company.size(); ++i) {
		outf << company[i].first << ' ';
		outf << convert(company[i].second.first) << ' ';
		outf << convert(company[i].second.second);
		outf << '\n';
	}
}

std::string convert(int k) { //функция перевода времени из int в string
	std::string time{ "" };
	std::string s;
	if (k / 60 < 10)
		s = "0" + std::to_string(k / 60);
	else
		s = std::to_string(k / 60);
	time += s + ':';
	if (k % 60 < 10)
		s = "0" + std::to_string(k % 60);
	else
		s= std::to_string(k % 60);
	time += s;
	return time;
}