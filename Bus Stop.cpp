#include <iostream>
#include <fstream>

#include "Timetable.h"

void print(std::vector <T>& company, std::ofstream& outf);

std::string convert(int k);

int main() {
	std::ifstream inf("input.txt");
	std::ofstream outf("output.txt");

	Timetable general;

	std::vector <T> Posh;
	std::vector <T> Grotty;

	int n = 0;

	while (inf) { //adding data from a file to a data structure
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

	general.sort().task(Posh, Grotty); //sorting and doing the job

	print(Posh, outf);
	if (Posh.size() != 0)
		outf << '\n';
	print(Grotty, outf);

	return 0;
}

void print(std::vector <T>& company, std::ofstream& outf) { //function for writing data to an output file
	for (int i = 0; i < company.size(); ++i) {
		outf << company[i].company << ' ';
		outf << convert(company[i].leave) << ' ';
		outf << convert(company[i].arrive);
		outf << '\n';
	}
}

std::string convert(int k) { //function for converting time from int to string
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
		s = std::to_string(k % 60);
	time += s;
	return time;
}