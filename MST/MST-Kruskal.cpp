#include <iostream>
#include <algorithm>
#include "UnionFind.h"		//并查集

using namespace std;

//边
struct edg
{
	int u;
	int v;
	int len;
}edgs[MAX];

auto comp = [](edg e1, edg e2){return e1.len < e2.len; };

int Kruskal(int n, int m){//n个点，m条边  
	sort(edgs, edgs + m, comp);//对边长排序  
	int sum = 0;
	int cnt = 0;

	//从小到大枚举边
	for (int i = 0; i < m; i++){
		int u = edgs[i].u;
		int v = edgs[i].v;
		int len = edgs[i].len;

		//两个点非连通时才加入，连通时不作任何处理
		if (FindSet(u) != FindSet(v)){
			sum += len;
			UnionSet(u, v);
			cnt++;
		}
	}
	//如果加入n-1条边，则图是连通的；否则图不连通
	return cnt == n - 1 ? sum : -1;
}

int main(){
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++){
		cin >> edgs[i].u >> edgs[i].v >> edgs[i].len;
	}
	for (int i = 1; i <= n; i++)
		MakeSet(i);
	int res = Kruskal(n, m);
	if (res == -1)
		cout << "Not all connected!" << endl;
	else
		cout << "Min len: " << res << endl;

	system("pause");
}