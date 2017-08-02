#include <iostream>
#include <algorithm>

using namespace std;


//最短路径问题
const int MAXINT = 32767;
const int MAXNUM = 7;

int G[MAXNUM][MAXNUM] = {
	{0,7,9,3,-1,-1,-1},
	{7,0,-1,-1,3,9,-1},
	{9,-1,0,5,-1,-1,8},
	{3,-1,5,0,-1,1,-1},
	{-1,3,-1,-1,0,4,-1},
	{-1,9,-1,1,4,0,2},
	{-1,-1,8,-1,-1,2,0}
};

class Floyd
{
public:
	int A[MAXNUM][MAXNUM];
	int path[MAXNUM][MAXNUM];
	void solve(int v0)
	{
		for (int i = 0; i < MAXNUM; ++i)
		{
			for (int j = 0; j < MAXNUM; ++j)
			{
				A[i][j] = G[i][j];
				path[i][j] = j;
			}
		}
		for (int k = 0; k < MAXNUM; ++k)
		{
			for (int i = 0; i < MAXNUM; ++i)
			{
				for (int j = 0; j < MAXNUM; ++j)
				{
					if (A[i][k] + A[k][j] < A[i][j])
					{
						A[i][j] = A[i][k] + A[k][j];
						path[i][j] = path[i][k];
					}
				}
			}
		}
	}
};

int main()
{
	for (int i = 0; i < MAXNUM; ++i)
	{
		for (int j = 0; j < MAXNUM; ++j)
		{
			if (G[i][j] < 0)
				G[i][j] = MAXINT;
		}
	}

	int s = 0;		//起点
	Floyd f;
	f.solve(s);
	cout << "Floyd：" << endl;
	for (int i = 0; i < 7; ++i)
	{
		cout << s + 1 << " -> " << i + 1 << " min distance: " << dist[i];
		cout << ",  path: " << i + 1 << " <- ";
		int p = f.path[i][s];
		while (p != s)
		{
			cout << p + 1 << " <- ";
			p = f.path[p][s];
		}
		cout << s + 1 << endl;
	}

	cout <<endl;
	
	return 0;
}