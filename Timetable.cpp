#include <algorithm>

#include "Timetable.h"

void Timetable::add(std::string s, int n) {  //add data to structure 
	if (n == 0)
		timetable.push_back({ s,0,0 });
	else {
		int k = 60 * stoi(s.substr(0, 2)) + stoi(s.substr(3, 2));
		if (n == 1)
			timetable[timetable.size() - 1].leave = k;
		else
			timetable[timetable.size() - 1].arrive = k;
	}
}

bool comp(T& v_1, T& v_2) { //comparator for sorting data structure by arrival time
	return v_1.arrive < v_2.arrive;
}

bool comp_task(T& v_1, T& v_2) { //comparator for sorting the data structure by departure time
	return v_1.leave < v_2.leave;
}

Timetable& Timetable::sort() { //sort the data structure by arrival time
	std::sort(timetable.begin(), timetable.end(), comp);
	return *this;
}

void sort_task(std::vector <T>& timetable) { //sorting the data structure by departure time
	std::sort(timetable.begin(), timetable.end(), comp_task);
}

void erase_el(std::vector <T>& timetable, int& pos) { //removing an item from the data structure
	std::vector <T>::iterator it;
	it = timetable.begin() + pos;
	timetable.erase(it);
	--pos;
}

void Timetable::task(std::vector <T>& Posh, std::vector <T>& Grotty) { //function of the task

	for (int b = 0; b < timetable.size(); ++b) { // this cycle is designed to remove from the data structure cases where the bus travels for more than an hour
		if (timetable[b].arrive - timetable[b].leave > 60 || timetable[b].leave > timetable[b].arrive) {
			if (timetable[b].leave > timetable[b].arrive) {
				if (timetable[b].leave > 1380 && timetable[b].arrive < 60) {
					if (timetable[b].arrive + 1440 - timetable[b].leave > 60) {
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

	if (timetable.size() == 1) {
		if (timetable[0].company == "Posh")
			Posh.push_back(timetable[0]);
		else
			Grotty.push_back(timetable[0]);
		return;
	}

	while (timetable[i].arrive < 60) { //this cycle is designed to check cases in which the arrival time is less than 01:00, because their dispatch time can be up to 00:00
		int i_leave = timetable[i].leave;
		int i_arrive = timetable[i].arrive;
		int pr_leave, pr_arrive;//pr-previous
		if (i_leave < 60)
			i_leave += 1440;
		i_arrive += 1440;
		pr_leave = timetable[i - 1].leave;
		pr_arrive = timetable[i - 1].arrive;
		if (pr_leave < 60)
			pr_leave += 1440;
		if (pr_arrive < 60)
			pr_arrive += 1440;
		if (pr_leave == i_leave) { //if dispatch time is the same
			if (pr_arrive == i_arrive) { //if arrival time and departure time are the same
				if (timetable[i - 1].company == "Grotty") {
					--i;
					erase_el(timetable, i);
					++i;
				}
				else {
					erase_el(timetable, i);
				}
			}
			else { //since the data structure is sorted by arrival time and departure time is the same, arrival time is different, then we must delete the current element, since its arrival time is bigger.
				erase_el(timetable, i);
			}
		}
		else {// dispatch time is different
			if (pr_leave > i_leave) {//the arrival time of "i" element is greater than or equal to "i-1", which means if its dispatch time is less, then we must delete it
				erase_el(timetable, i);
			}
			else {
				if (pr_arrive == i_arrive) {//the dispatch time of our "i" element is greater, so if its arrival time is equal to the arrival time of the "i-1" element, then we must remove "i-1"
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

	for (; i < timetable.size(); ++i) {//this cycle is for other cases

		if (timetable[i].leave == timetable[i - 1].leave) {//same as for the previous while loop
			if (timetable[i].arrive == timetable[i - 1].arrive) {
				if (timetable[i].company == "Grotty") {
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
		else {//Here, unlike the while loop, we need an additional check to see if our previous element will have a send time after 23:00 
			if (timetable[i].leave < timetable[i - 1].leave) {//for example, our first element is 23:20 00:20 and the next one is 16:40 16:50. If there was a check, as in a while loop, I would remove the "i" 
				if (timetable[i - 1].leave >= 1380) {         //element, although I really don't need to remove it. This check is needed precisely for this.
					if (timetable[i - 1].leave - timetable[i].leave < 60)
						erase_el(timetable, i);
				}
				else
					erase_el(timetable, i);
			}
			else {//same as for the previous while loop
				if (timetable[i].arrive == timetable[i - 1].arrive) {
					--i;
					erase_el(timetable, i);
					++i;
				}
			}
		}
	}

	i = 0;

	while (timetable[i].leave >= 1380 && timetable[i].arrive < 60) {//this loop is for a specific case, for example 23:40 23:59 the last element and 23:40 00:10 the zero element.Then we have to remove the zero
		if (timetable[timetable.size() - 1].leave >= 1380 && timetable[timetable.size() - 1].arrive < 1440) { //element.
			if (timetable[timetable.size() - 1].leave >= timetable[i].leave) {
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
		if (timetable[i].company == "Posh")
			Posh.push_back(timetable[i]);
		else
			Grotty.push_back(timetable[i]);
	}
}
