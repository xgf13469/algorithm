#include <iostream>
#include <algorithm>

using namespace std;

//最短路径问题
const int MAXINT = 32767;
const int MAXNUM = 7;
int dist[MAXNUM];
int pre[MAXNUM];

int G[MAXNUM][MAXNUM] = {
	{0,7,9,3,-1,-1,-1},
	{7,0,-1,-1,3,9,-1},
	{9,-1,0,5,-1,-1,8},
	{3,-1,5,0,-1,1,-1},
	{-1,3,-1,-1,0,4,-1},
	{-1,9,-1,1,4,0,2},
	{-1,-1,8,-1,-1,2,0}
};

class Dijkstra
{
public:
	void solve(int v0)
	{
		bool s[MAXNUM];
		for (int i = 0; i < MAXNUM; ++i)
		{
			dist[i] = G[v0][i];
			s[i] = false;
			
			if (dist[i] == MAXINT)
				pre[i] = -1;
			else
				pre[i] = v0;
		}

		dist[v0] = 0;
		s[v0] = true;
		for (int i = 1; i < MAXNUM; ++i)
		{
			int mindist = MAXINT;
			int u = v0;
			for (int j = 0; j < MAXNUM; ++j)
				if (!s[j] && dist[j] < mindist)
				{
					u = j;
					mindist = dist[j];
				}
		
			s[u] = true;

			for (int j = 0; j < MAXNUM; ++j)
				if (!s[j] && G[u][j] < MAXINT)
				{
					if (dist[u] + G[u][j] < dist[j])
					{
						dist[j] = dist[u] + G[u][j];
						pre[j] = u;
					}
				}
		}
	}
	
	void getPath(int v0)
	{
		solve(v0);

		//输出v0到其他所有节点的最短路径。注意：输出顺序是反向的！！！
		for (int i = 0; i < MAXNUM; ++i)
		{
			cout << v0 << " -> " << i << " min distance: " << dist[i];
			cout << ",  path: " << i << " <- ";
			int p = pre[i];
			while (p != v0)
			{
				cout << p << " <- ";
				p = pre[p];
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
	Dijkstra d;
	d.getPath(s);

	return 0;
}