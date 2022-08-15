#pragma once
#ifndef IncMatrx_H
#define IncMatrx_H

#include "matrxAju.h"
#include "Dfs.h"
#include <vector>
using namespace std;

class incMat
{
public:
	void setInc(const int& picks, int& lines, const vector<vector<int>>& m_newAju, vector<vector<int>>& m_incM);
	void weights(const int& picks, const int& lines, vector <int>& m_weights, vector<vector<int>> m_incM);
	void cycleGraf(int picks);

private:
	vector <vector <int>> m_incM;
	vector <int> m_weigths;
	int lines;
};

#endif
