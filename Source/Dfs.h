#pragma once
#ifndef Dfs_H
#define Dfs_H

#include <stack>
#include <vector>

using namespace std;

class dfs
{
public:
	int checking(const int& picks,const vector<vector<int>>& vec);
	void stepping(const int& picks,vector<vector<int>> vec,vector<int>& m_aju, vector<int>& m_aju_2);
	void setNewMat(const int& picks, const vector<int>& m_aju, vector<vector<int>>& m_newAju,const vector<vector<int>>& m_matAju, const vector<int>& m_aju_2);
private:
	int picks = 0;
	vector<int>m_aju;
	vector<int>	m_aju_2;
	vector<vector<int>> m_newAju;
};

#endif 
