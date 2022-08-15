#include <iostream>
#include <string>
#include <queue>
#include <clocale>

#include "Dfs.h"
#include "matrxAju.h"
#include "IncMatrx.h"

using namespace std;

enum Mode
{
	_file,
	_handmade
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int picks = 0; int lines = 0;

	vector<vector<int>> m_matAju;
	vector<vector<int>> m_newAju;
	vector<vector<int>> m_incM;
	vector<int> m_weights;
	vector<int> m_aju;
	vector<int> m_aju_2;

	matrxAju matAju;
	dfs f_dfs;
	incMat f_inc;
	int mode = 0;

	cout << "Загрузить данные из файла или ввести вручную[0/1]: ";
	cin >> mode;

	if (mode == _file) 
	{
		matAju.setAjuByFile(picks, m_matAju);
	}
	else if(mode == _handmade)
	{
		matAju.setSize(picks);
		matAju.setAju(picks, m_matAju);
	}
	matAju.displayAju(picks, m_matAju);

	int t = f_dfs.checking(picks,m_matAju);

	if (t == 1)
	{
		f_inc.cycleGraf(picks);
		return 0;
	}
	if (t == 2)
	{
		f_dfs.stepping(picks, m_matAju, m_aju, m_aju_2);
		f_dfs.setNewMat(picks, m_aju, m_newAju, m_matAju, m_aju_2);
	}
	if (t == 3)
	{
		m_newAju = m_matAju;
		cout << endl;
	}

	f_inc.setInc(picks, lines, m_newAju, m_incM);
	f_inc.weights(picks, lines, m_weights, m_incM);
	system("pause >> void");
	return 0;
}