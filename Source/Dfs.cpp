#include <iostream>
#include <stack>
#include <iterator>
#include <algorithm>

#include "Dfs.h"

using namespace std;

int dfs::checking(const int& picks,const vector<vector<int>>& vec)
{
	int check = 0;
	int k = picks - 1;
	for (int i = 1; i < picks; i++)
	{
		for (int j = 0; j < (picks - k); j++)//До этого стояло какое-то не понятное условие (picks-i), Причем ВЕРНОЕ
		{
			if (vec.at(i).at(j) > 0) check++; //проверка на непральноориентированность, типа если из 3 -> 1
		}
		k--;
	}

	int s = 0;
	for (int i = 0; i < picks; i++)
	{
		vector<int> temporary = vec.at(i);
		int k = 0;
		for (int j = 0; j < picks; j++)
		{
			if (temporary.at(j) == 0)
				k++;
		}
		if (k < picks) s++;
	}

	cout << "Граф ";

	if (s == picks)
	{
		cout << "цикличен" << endl;
		cout << endl;
		return 1;
	}
	else
	{
		if (check > 0)
		{
			cout << "не правильно ориентирован *(требуется сортировка)*" << endl;
			cout << endl;
			return 2;
		}
		else
		{
			cout << "верно ориентирован, сортировка не требуется" << endl;
			cout << endl;
			return 3;
		}
	}	
	cout << endl;
}

void dfs::stepping(const int& picks, vector<vector<int>> m_matAju, vector<int>& m_aju, vector<int>& m_aju_2)
{
	int i, pick, j, temp = picks;
	pick = 0;
	vector<vector<int>>& vec = m_matAju;
	vector<int> vec_2;
	cout << "Перемещение вершин:" << endl;
	while (pick < picks)
	{
		int s = 0;
		for (i = 0; i < picks; i++)
		{
			vector<int> temporary = vec.at(i);
			int k = 0;
			for (j = 0; j < picks; j++)
			{
				if (temporary.at(j) == 0)
					k++;
			}
			if (k == temp && k!=0)
			{
				cout << "\t" <<  i+1 <<  " --> " << k << endl;
				m_aju.insert(m_aju.begin(), i);
				for (j = 0; j < picks; j++)
				{
					vector <int>& temporary = vec.at(j);
					temporary.at(i) = INT16_MAX;
					vec.at(i).at(j) = INT16_MAX;
				}
				temp--;
				pick++;
			}
		}
	}
	cout << endl;
}

void dfs::setNewMat(const int& picks, const vector<int>& m_aju, vector<vector<int>>& m_newAju, const vector<vector<int>>& m_matAju, const vector<int>& m_aju_2)
{
	int t;
	int k = 0;
	vector <int> temporary;
	for (int i = 0; i < picks; i++)
	{
		temporary.clear();
		for (int j = 0; j < picks; j++)
		{
			temporary.push_back(0);		
		}
		m_newAju.push_back(temporary);
	}
	for (int i : m_aju)
	{
		if (k < picks)
		{
			t = 0;
			for(int j : m_aju)
			{
				if (t < picks)
				{
					m_newAju.at(k).at(t) = m_matAju.at(i).at(j);
				}
				t++;
			}
		    
		}
		k++;
	}
	cout << "Матрица смежности для правильно ориентированного графа: " << endl;
	cout << endl;
	for (int i = 0; i < picks; i++)
	{
		for (int j = 0; j < picks; j++)
		{
			cout << " " <<m_newAju.at(i).at(j);
		}
		cout << endl;
	}
	cout << endl;
}
