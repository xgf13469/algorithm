#include <string>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//深度优先搜索
void dfs(vector<vector<int>> &graph, int node, vector<int>&visit, vector<int>&father)
{
	int n = graph.size();
	visit[node] = 1;

	for (int i = 0; i < n; i++)
		if (i != node && graph[node][i] != -1)
		{
			if (visit[i] == 1 && i != father[node])	//找到一个环
			{
				int tmp = node;
				cout << "cycle:";
				while (tmp != i)
				{
					cout << tmp << "->";
					tmp = father[tmp];
				}
				cout << tmp << endl;
			}
			else if (visit[i] == 0)
			{
				father[i] = node;
				dfs(graph, i, visit, father);
			}
		}
	visit[node] = 2;
}

int main()
{
	vector<vector<int>> g({ { 0, 1, -1 }, { -1, 0, 1 }, {1,-1,0} });

	int n = g.size();
	vector<int> visit(n, 0); //visit分为三种状态
	vector<int> father(n, -1);//father记录遍历过程中i的父节点
		
	for (int i = 0; i < n; i++)
		if (visit[i] == 0)
			dfs(g, i, visit, father);

	return 0;
}