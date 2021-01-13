#include <algorithm>

#include "Timetable.h"

void Timetable::add(std::string s, int n) {  //������ ���������� � ��������� ������
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

bool comp(std::pair<std::string, std::pair<int, int>>& v_1, std::pair<std::string, std::pair<int, int>>& v_2) { //comparator ��� ���������� ��������� ������ �� ������� ��������
	return v_1.second.second < v_2.second.second;
}

bool comp_task(std::pair<std::string, std::pair<int, int>>& v_1, std::pair<std::string, std::pair<int, int>>& v_2) { //comparator ��� ���������� ��������� ������ �� ������� �����������
	return v_1.second.first < v_2.second.first;
}

Timetable& Timetable::sort() { //���������� ��������� ������ �� ������� ��������
	std::sort(timetable.begin(), timetable.end(),comp);
	return *this;
}

void sort_task(std::vector <std::pair<std::string, std::pair<int, int>>>& timetable) { //���������� ��������� ������ �� ������� �����������
	std::sort(timetable.begin(), timetable.end(), comp_task);
}

void erase_el(std::vector <std::pair<std::string, std::pair<int, int>>>& timetable, int& pos) { //�������� �������� �� ��������� ������
	std::vector <std::pair<std::string, std::pair<int, int>>>::iterator it;
	it = timetable.begin() + pos;
	timetable.erase(it);
	--pos;
}

void Timetable::task(std::vector <std::pair<std::string, std::pair<int, int>>>& Posh, std::vector <std::pair<std::string, std::pair<int, int>>>& Grotty) { //������� ������ �������

	for (int b = 0; b < timetable.size(); ++b) { // ������ ���� ������������ ��� �������� �� ��������� ������ �������, ��� ������� ���� ������ ����
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

	while (timetable[i].second.second < 60) { //������ ���� ������������ ��� �������� �������, � ������� ����� �������� ������ 01:00, �.�. �� ����� �������� ����� ���� �� 00:00
		int i_f = timetable[i].second.first;// _f- ����� ��������, _s-����� ��������
		int i_s = timetable[i].second.second;
		int pr_f, pr_s;//i-1 �������
		if (i_f < 60)
			i_f += 1440;
		i_s += 1440;
		pr_f = timetable[i - 1].second.first;
		pr_s = timetable[i - 1].second.second;
		if (pr_f < 60)
			pr_f += 1440;
		if (pr_s < 60)
			pr_s += 1440;
		if (pr_f == i_f) { //���� ����� �������� ����������
			if (pr_s == i_s) { //���� ����� �������� � ����� �������� ����������
				if (timetable[i - 1].first == "Grotty") {
					--i;
					erase_el(timetable, i);
					++i;
				}
				else {
					erase_el(timetable, i);
				}
			}
			else { //�.�. ��������� ������ ������������� �� ������� ������� � ����� �������� ����������, ����� �������� ������, �� �� ������ ������� ������� �������, �.�. ��� ����� �������� ������.
				erase_el(timetable, i);
			}
		}
		else {// ����� �������� ������
			if (pr_f > i_f) {//����� �������� ������ i �������� ������ ��� �����, ������ ���� ��� ����� �������� ������, �� �� ������ ��� �������
				erase_el(timetable, i);
			}
			else {
				if (pr_s == i_s) {//����� �������� ������ i �������� ������, ������ ���� ��� ����� �������� ����� ������� �������� i-1 ��������, �� �� ������ ������� i-1 
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

	for (; i < timetable.size(); ++i) {//������ ���� ������������ ��� ������ �������
		
		if (timetable[i].second.first == timetable[i - 1].second.first) {//����� �� ��� � ��� �������� ����� while
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
		else {//��� � ������� �� ����� while ����� ���. �������� �� ��, �� ����� �� � ������ ����������� �������� ����� �������� ����� 23:00  
			if (timetable[i].second.first < timetable[i - 1].second.first) {// � ������� ��� ������ ������� 23:20 00:20 � ��������� 16:40 16:50. ���� �� ���� �������� ��� � ����� while, � �� ������ ������� i, 
				if (timetable[i - 1].second.first >= 1380) {               // ���� �� ����� ���� ������� ��� �� ����. ��� �������� ������ ��� ����� � �����.
					if (timetable[i - 1].second.first - timetable[i].second.first < 60)
						erase_el(timetable, i);
				}
				else
					erase_el(timetable, i);
			}
			else {//����� �� ��� � ����� while
				if (timetable[i].second.second == timetable[i - 1].second.second) {
					--i;
					erase_el(timetable, i);
					++i;
				}
			}
		}
	}

	i = 0; 

	while (timetable[i].second.first >= 1380 && timetable[i].second.second < 60) {//������ ���� ������������ ��� ����������� ������, �������� 23:40 23:59 ��������� ������� � 23:40 00:10 ������� �������.����� �� ������
		if (timetable[timetable.size() - 1].second.first >= 1380 && timetable[timetable.size() - 1].second.second<1440) { // ������� ������� �������.
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
