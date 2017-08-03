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
	int path[MAXNUM][MAXNUM];
	void solve(int v0)
	{
		for (int i = 0; i < MAXNUM; ++i)
			for (int j = 0; j < MAXNUM; ++j)
				path[i][j] = j;

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
	
	void getPath(int v0)
	{
		solve(v0);

		//输出最短路径。同样是反向的！！！
		for (int i = 0; i < MAXNUM; ++i)
		{
			cout << v0 << " -> " << i << " min distance: " << dist[i];
			cout << ",  path: " << i << " <- ";
			int p = path[i][v0];
			while (p != v0)
			{
				cout << p << " <- ";
				p = path[p][v0];
			}
			cout << v0 << endl;
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
	f.getPath(s);
	
	return 0;
}