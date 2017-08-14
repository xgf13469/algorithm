#include <iostream>
#include <algorithm>
#include "UnionFind.h"		//���鼯

using namespace std;

//��
struct edg
{
	int u;
	int v;
	int len;
}edgs[MAX];

auto comp = [](edg e1, edg e2){return e1.len < e2.len; };

int Kruskal(int n, int m){//n���㣬m����  
	sort(edgs, edgs + m, comp);//�Ա߳�����  
	int sum = 0;
	int cnt = 0;

	//��С����ö�ٱ�
	for (int i = 0; i < m; i++){
		int u = edgs[i].u;
		int v = edgs[i].v;
		int len = edgs[i].len;

		//���������ͨʱ�ż��룬��ͨʱ�����κδ���
		if (FindSet(u) != FindSet(v)){
			sum += len;
			UnionSet(u, v);
			cnt++;
		}
	}
	//�������n-1���ߣ���ͼ����ͨ�ģ�����ͼ����ͨ
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