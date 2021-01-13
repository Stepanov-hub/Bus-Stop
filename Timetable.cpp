#include <algorithm>

#include "Timetable.h"

void Timetable::add(std::string s, int n) {  //функия добавления в структуру данных
	if (n == 0)
		timetable.push_back({ s, {} });
	else {
		int k = 60 * stoi(s.substr(0, 2)) + stoi(s.substr(3, 2));
		if(n==1)
			timetable[timetable.size() - 1].second.first=k;
		else
			timetable[timetable.size() - 1].second.second = k;
	}
}

bool comp(std::pair<std::string, std::pair<int, int>>& v_1, std::pair<std::string, std::pair<int, int>>& v_2) { //comparator для сортировки структуры данных по времени прибытия
	return v_1.second.second < v_2.second.second;
}

bool comp_task(std::pair<std::string, std::pair<int, int>>& v_1, std::pair<std::string, std::pair<int, int>>& v_2) { //comparator для сортировки структуры данных по времени отправления
	return v_1.second.first < v_2.second.first;
}

Timetable& Timetable::sort() { //сортировка структуры данных по времени прибытия
	std::sort(timetable.begin(), timetable.end(),comp);
	return *this;
}

void sort_task(std::vector <std::pair<std::string, std::pair<int, int>>>& timetable) { //сортировка структуры данных по времени отправления
	std::sort(timetable.begin(), timetable.end(), comp_task);
}

void erase_el(std::vector <std::pair<std::string, std::pair<int, int>>>& timetable, int& pos) { //удаление элемента из структуры данных
	std::vector <std::pair<std::string, std::pair<int, int>>>::iterator it;
	it = timetable.begin() + pos;
	timetable.erase(it);
	--pos;
}

void Timetable::task(std::vector <std::pair<std::string, std::pair<int, int>>>& Posh, std::vector <std::pair<std::string, std::pair<int, int>>>& Grotty) { //функция самого задания

	for (int b = 0; b < timetable.size(); ++b) { // данный цикл предназначен для удаления из структуры данных случаев, где автобус едет больше часа
		if (timetable[b].second.second - timetable[b].second.first > 60 || timetable[b].second.first > timetable[b].second.second) {
			if (timetable[b].second.first > timetable[b].second.second) {
				if (timetable[b].second.first > 1380 && timetable[b].second.second < 60) {
					if (timetable[b].second.second + 1440 - timetable[b].second.first > 60) {
						erase_el(timetable, b);
					}
				}
				else {
					erase_el(timetable, b);
				}
			}
			else {
				erase_el(timetable, b);
			}
		}
	}

	int i = 1;

	if (timetable.size() == 0)
		return;

	if(timetable.size()==1){
		if (timetable[0].first == "Posh") 
			Posh.push_back(timetable[0]);
		else
			Grotty.push_back(timetable[0]);
		return;
	}

	while (timetable[i].second.second < 60) { //данный цикл предназначен для проверки случаев, в которых время прибытия меньше 01:00, т.к. их время отправки может быть до 00:00
		int i_f = timetable[i].second.first;// _f- время отправки, _s-время прибытия
		int i_s = timetable[i].second.second;
		int pr_f, pr_s;//i-1 элемент
		if (i_f < 60)
			i_f += 1440;
		i_s += 1440;
		pr_f = timetable[i - 1].second.first;
		pr_s = timetable[i - 1].second.second;
		if (pr_f < 60)
			pr_f += 1440;
		if (pr_s < 60)
			pr_s += 1440;
		if (pr_f == i_f) { //если время отправки одинаковое
			if (pr_s == i_s) { //если время прибытия и время отправки одинаковое
				if (timetable[i - 1].first == "Grotty") {
					--i;
					erase_el(timetable, i);
					++i;
				}
				else {
					erase_el(timetable, i);
				}
			}
			else { //т.к. структура данных отсортирвоана по времени приезда и время отправки одинаковое, время прибытия разное, то мы должны удалить текущий элемент, т.к. его время прибытия больше.
				erase_el(timetable, i);
			}
		}
		else {// время отправки разное
			if (pr_f > i_f) {//время прибытия нашего i элемента больше или равно, значит если его время отправки меньше, то мы должны его удалить
				erase_el(timetable, i);
			}
			else {
				if (pr_s == i_s) {//время отправки нашего i элемента больше, значит если его время прибытия равно времени прибытия i-1 элемента, то мы должны удалить i-1 
					--i;
					erase_el(timetable, i);
					++i;
				}
			}
		}
		++i;
		if (i == timetable.size())
			break;
	}

	for (; i < timetable.size(); ++i) {//данный цикл предназначен для других случаев
		
		if (timetable[i].second.first == timetable[i - 1].second.first) {//такой же как и для прошлого цикла while
			if (timetable[i].second.second == timetable[i - 1].second.second) {
				if (timetable[i].first == "Grotty") {
					erase_el(timetable, i);
				}
				else {
					--i;
					erase_el(timetable, i);
					++i;
				}
			}
			else {
				erase_el(timetable, i);
			}
		}
		else {//Тут в отличие от цикла while нужна доп. проверка на то, не будет ли у нашего предыдущего элемента время отправки после 23:00  
			if (timetable[i].second.first < timetable[i - 1].second.first) {// к примеру наш первый элемент 23:20 00:20 а следующий 16:40 16:50. Если бы была проверка как в цикле while, я бы удалил элемент i, 
				if (timetable[i - 1].second.first >= 1380) {               // хотя на самом деле удалять его не надо. Эта проверка именно для этого и нужна.
					if (timetable[i - 1].second.first - timetable[i].second.first < 60)
						erase_el(timetable, i);
				}
				else
					erase_el(timetable, i);
			}
			else {//такой же как в цикле while
				if (timetable[i].second.second == timetable[i - 1].second.second) {
					--i;
					erase_el(timetable, i);
					++i;
				}
			}
		}
	}

	i = 0; 

	while (timetable[i].second.first >= 1380 && timetable[i].second.second < 60) {//данный цикл предназначен для конкретного случая, например 23:40 23:59 последний элемент и 23:40 00:10 нулевой элемент.Тогда мы должны
		if (timetable[timetable.size() - 1].second.first >= 1380 && timetable[timetable.size() - 1].second.second<1440) { // удалить нулевой эоемент.
			if (timetable[timetable.size() - 1].second.first >= timetable[i].second.first) {
				erase_el(timetable, i);
			}
			else {
				break;
			}
		}
		else {
			break;
		}
		++i;
	}

	sort_task(timetable);

	for (int i = 0; i < timetable.size(); ++i) {
		if (timetable[i].first == "Posh")
			Posh.push_back(timetable[i]);
		else
			Grotty.push_back(timetable[i]);
	}
}
