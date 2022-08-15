#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "IncMatrx.h"


using namespace std;

int FindMin(int** arr, int picks, int iteration); 
int getLengthFromInc(int from, int to, vector<vector<int>> m_inc);

void incMat::setInc(const int& picks, int& lines, const vector<vector<int>>& m_newAju, vector<vector<int>>& m_incM)
{
	lines = 0;
	int cols = 0; int rows = 0;
	for (int i = 0; i < picks; i++)//Узнаю сколько дуг
	{
		for (int j = 0; j < picks; j++)
		{
			if (m_newAju.at(i).at(j) != 0) lines++;
		}
	}
	for (int i = 0; i < picks; i++)//Инициализирую матрицу инцидентности
	{
		vector <int> temporary;
		temporary.clear();
		for (int j = 0; j < lines; j++)
		{
			temporary.push_back(0);
		}
		m_incM.push_back(temporary);
	}
	for (int i = 0; i < picks; i++)//Заполняю ее
	{
		for (int j = 0; j < picks; j++)
		{
			if (m_newAju.at(i).at(j) != 0 && rows < lines)
			{ 
				cols = i;
				m_incM.at(cols).at(rows) = -m_newAju.at(i).at(j);
				cols = j;
				m_incM.at(cols).at(rows) = m_newAju.at(i).at(j);
				rows++;
			}
		}
	}
	cout << "Incidence matrix: " << endl;
	for (int i = 0; i < picks; i++)//Вывод в консоль
	{
		for (int j = 0; j < lines; j++)
		{
			cout <<" "<< setw(2) << m_incM.at(i).at(j);
		}
		cout << endl;
	}
	cout << endl;
}

void incMat::weights(const int& picks, const int& lines, vector <int>& m_weights, vector<vector<int>> m_incM)
{
	int start, 
		finish, 
		iterat_index= 0;
	
	vector<vector<int>>& vec = m_incM;

	int* temp_arr = new int[picks];
	for (int i = 0; i < picks; i++)
	{
		temp_arr[i] = 0;
	}

	int** wayS = new int* [picks];
	for (int i = 0; i < lines; i++)
	{
		wayS[i] = new int[picks];
	}
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < picks; j++)
		{
			wayS[i][j] = INT16_MIN; //все позиции помечаются как БЕСКОНЕЧНОСТЬ
		}
	}

	for (int i = 0; i < picks; i++)
	{
		for (int j = 0; j < lines; j++)
		{
			if(m_incM[i][j] < 0) {
				m_weights.push_back(-m_incM[i][j]);
			}
		}
	}
	cout << "Начальная позиция: "; cin >> start;
	cout << "Конечная позиция: "; cin >> finish;
	while (start >= finish)
	{
		start = finish = 0;
		cout << "Введите корректные значения(Начальная < Конечная)\n";
		cin.clear();
		cout << "Начальная позиция: "; cin >> start;
		cout << "Конечная позиция: "; cin >> finish;
		
	}
	while (start <= 0 || finish <= 0 || start > picks || finish > picks)
	{
		start = finish = 0;
		cout << "Значения вне границ, требуется [1 <= Начальная < Конечная <= Кол-во вершин].";
		cout << "Кол-во вершин - " << picks << endl;
		cin.clear();
		cout << "Начальная позиция: "; cin >> start;
		cout << "Конечная позиция: "; cin >> finish;
	}

	int t = start - 1;
	int lastWeight = 0;
	iterat_index = 0;

	for (int i = 0; i < picks; i++)
	{	
		for (int j = 0; j < lines; j++)
		{
			if (vec.at(t).at(j) < 0)
			{
				for (int k = 0; k < picks; k++)
				{
					if (vec.at(k).at(j) > 0)
					{
						if (wayS[iterat_index][k] == INT16_MIN)//Снятие пометки БЕСКОНЕЧНОСТЬ
							wayS[iterat_index][k] = INT16_MAX;

						if (iterat_index == 0) {
							wayS[iterat_index][k] = m_weights.at(j);
						}
						else
						{
							if (wayS[iterat_index - 1][k] == INT16_MIN)//Снятие пометки БЕСКОНЕЧНОСТЬ
								wayS[iterat_index - 1][k] = INT16_MAX;

							wayS[iterat_index][k] = (m_weights.at(j) + lastWeight < wayS[iterat_index - 1][k]) ? m_weights.at(j) + lastWeight : wayS[iterat_index - 1][k];
						}
					}
				}
			}
		}

		int index = FindMin(wayS, picks, iterat_index);
		if (index == finish - 1) {
			temp_arr[index] = lastWeight = wayS[iterat_index][index];
			break;
		}
		else {
			t = index;
			temp_arr[index] = lastWeight = wayS[iterat_index][index];
			wayS[iterat_index][index] = INT16_MIN;
			iterat_index++;
		}
	}

	int curr_length = wayS[iterat_index][finish - 1];
	int current_index = finish - 1;
	vector<int> oneShortWay;
	oneShortWay.push_back(finish - 1);
	while(curr_length > 0)
	{
		for (int pick = 0; pick < picks; pick++)
		{
			if (temp_arr[current_index] == temp_arr[pick] + getLengthFromInc(pick, current_index, m_incM))
			{
				curr_length -= getLengthFromInc(pick, current_index, m_incM);
				current_index = pick;
				oneShortWay.push_back(pick);
			}
		}
	}

	vector<int>(oneShortWay).swap(oneShortWay);
	while (oneShortWay.at(oneShortWay.size() - 1) != 0)
	{
		oneShortWay.erase(oneShortWay.begin() + oneShortWay.size() - 1);
		vector<int>(oneShortWay).swap(oneShortWay);
	}
	cout << "Кратчайший путь: s -> ";
	for (int i = oneShortWay.size() - 1; i >= 0; i--)
	{
		cout << oneShortWay[i] + 1 << " -> ";
	}
	cout << "t c длиной = " << wayS[iterat_index][finish - 1];
}

int getLengthFromInc(int from, int to, vector<vector<int>> m_inc)
{
	for (int i = 0; i < m_inc.at(0).size(); i++)
	{
		if (m_inc[from][i] < 0)
			if (m_inc[to][i] > 0)
				return m_inc[to][i];
	}
	return 0;
}

int findСonformity(int* arr, int value, int picks) 
{
	int index = 0;
	for (int i = 0; i < picks; i++)
	{
		if (arr[i] == value)
			index = i;
	}
	return index;
}

int FindMin(int** arr, int picks, int iteration) {
	int value = INT16_MAX;
	int index = 0;
	for (int i = 0; i < picks; i++)
	{
		if (value > arr[iteration][i] && arr[iteration][i] != INT16_MIN) {
			value = arr[iteration][i];
			index = i;
		}
	}
	return index;
}

void incMat::cycleGraf(int picks)
{
	vector <vector<int>> a;
	for (int i = 0; i < picks; i++)
	{
		vector<int> temporary;
		for (int j = 0; j < picks; j++)
		{
			temporary.push_back(0);
		}
		a.push_back(temporary);
	}
	vector<int> d;
	for (int i = 0; i < picks; i++)
	{
		d.push_back(0);
	}
	vector<int> v;
	for (int i = 0; i < picks; i++)
	{
		v.push_back(0);
	}
	int t = 0;
	int minindex, min;
	cout << "Input weights: " << endl;
	for (int i = 0; i < picks; i++)
	{
		a.at(i).at(i) = 0;
		for (int j = i + 1; j < picks; j++)
		{
			cin >> t;
			a.at(i).at(j) = t;
			a.at(j).at(i) = t;
		}
	}
	cout << "Matrix of weights: " << endl;
	for (int i = 0; i < picks; i++)
	{
		for (int j = 0; j < picks; j++)
		{
			cout << a.at(i).at(j) << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < picks; i++)
	{
		d.at(i) = 10000;
		v.at(i) = 1;
	}
	d.at(0) = 0;
	do
	{
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < picks; i++)
		{
			if (v.at(i) == 1 && d.at(i) < min)
			{
				min = d.at(i);
				minindex = i;
			}
		}
		if (minindex != 10000)
		{
			for (int i = 0; i < picks; i++)
			{
				if (a.at(minindex).at(i) > 0)
				{
					t = min + a.at(minindex).at(i);
					if (t < d.at(i))
					{
						d.at(i) = t;
					}
				}
			}
			v.at(minindex) = 0;
		}
	} while (minindex < 10000);
	cout << "Short ways to picks: " << endl;
	for (int i = 0; i < picks; i++)
	{
		cout << d.at(i) << " ";
	}
	cout << endl;
	vector<int> ver;
	for (int i = 0; i < picks; i++)
	{
		ver.push_back(0);
	}
	int end = picks - 1;
	ver.at(0) = end + 1;
	int k = 1;
	int weight = d.at(end);
	while (end > 0)
	{
		for (int i = 0; i < picks; i++)
		{
			if (a.at(end).at(i) != 0)
			{
				int t = weight - a.at(end).at(i);
				if (t == d.at(i))
				{
					weight = t;
					end = i;
					ver.at(k) = i + 1;
					k++;
				}
			}
		}
	}
	for (int i = k - 1; i >= 0; i--)
	{
		cout << ver.at(i) <<" ";
	}
	getchar();
}
