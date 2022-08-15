#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include "matrxAju.h"

using namespace std;

void matrxAju::setSize(int &picks)
{
	cout << "Задайте количество вершин графа: ";
	cin >> picks;
}

void matrxAju::setAjuByFile(int &picks, vector<vector<int>>& m_matAju)
{
	string path = "Graph.txt";
	ifstream fs(path);

	int rows = 0;
	int cols = 0;
	if (fs.is_open())
	{
		int temp;
		int count = 0;
		while (!fs.eof())
		{
			fs >> temp;
			count++;
		}

		fs.seekg(0, ios::beg);
		fs.clear();

		int spaces = 0;
		char symb;
		while (!fs.eof())
		{
			fs.get(symb);
			if (symb == ' ') spaces++;
			if (symb == '\n') break;
		}

		fs.seekg(0, ios::beg);
		fs.clear();

		rows = count / (spaces + 1);
		cols = spaces + 1;
		double** x;
		x = new double* [rows];
		for (int i = 0; i < rows; i++) x[i] = new double[rows];

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				fs >> x[i][j];
			}
		}
		m_matAju.clear();
		vector<int> temp_vec;
		for (int i = 0; i < rows; i++)
		{
			temp_vec.clear();
			for (int j = 0; j < cols; j++)
			{
				temp_vec.push_back(x[i][j]);
			}
			m_matAju.push_back(temp_vec);
		}
		picks = cols;
	}
}

void matrxAju::setAju(const int &picks, vector<vector<int>> &m_matAju)
{
	int aju;
	m_matAju.clear();
	vector <int> temporary;
	cout << "Введите значения:" << endl;
	wcout << setw(12) << "1|2|3" << endl;
	for (int i = 0; i < picks ; i++)
	{
		temporary.clear();
		cout << "[" << i + 1 << "] -> ";
		for (int j = 0; j < picks ; j++)
		{
			cin >> aju;
			while (aju < 0)
			{
				cin.clear();
				cout << "Неверное значение(требуется положительное). Повторный ввод: ";
				cout << "[" << i + 1 << "] = ";
				cin >> aju;
			}
			temporary.push_back(aju);
		}
		m_matAju.push_back(temporary);
	}
}



void matrxAju::displayAju(const int& picks, const vector<vector<int>>& m_matAju)
{
	cout << "Изначальные направления дуг: \n" << endl;
	for (int i = 0; i < picks; i++)
	{
		const vector<int> temporary = m_matAju.at(i);
		for (int j = 0; j < picks ; j++)
		{
			const int element = temporary.at(j);
			if (element > 1)
			{
				cout << "\t" << i+1 << " --> " << j+1 << endl;
			}
			
		}
	}
	cout << endl;
}

