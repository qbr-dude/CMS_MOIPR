#pragma once
#ifndef matrxAju_H
#define matrxAju_H

#include <vector>


using namespace std;

class matrxAju
{
public:
	void setSize(int &picks);
	void setAjuByFile(int& picks, vector<vector<int>>& m_matAju);
	void setAju(const int &picks, vector<vector<int>> &m_matAju);
	void displayAju(const int& picks, const vector<vector<int>> &vec);

private:
	vector <vector <int>> m_matAju;
	int picks = 0;
};



#endif