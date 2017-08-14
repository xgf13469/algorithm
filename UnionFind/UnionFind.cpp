#include <iostream>
using namespace std;


#define MAX 100
int father[MAX];   /* father[x]表示x的父节点*/
int Rank[MAX];     /* Rank[x]表示x的秩*/

//建立一个新的集合，每一个子节点就是一个数，本身就是他的根节点
void MakeSet(int x)
{
	father[x] = x;
	Rank[x] = 0;
}

//通过递归向上查找根节点，回溯时改变当前节点的父节点，直接指向根节点。
int FindSet(int x)
{
	if (x == father[x])
		return father[x];
	return FindSet(father[x]);
}

//两个集合的合并算法
void UnionSet(int x, int y)
{
	int GrandX = FindSet(x);
	int GrandY = FindSet(y);

	if (GrandX == GrandY)
		return;
	if (Rank[GrandX] < Rank[GrandY])
		father[GrandX] = GrandY;
	else
	{
		if (Rank[GrandX] == Rank[GrandY])
			Rank[GrandX]++;
		father[GrandY] = GrandX;
	}
}

//根节点
int roots[MAX];

int main(){
	int m,n;
	cin >> m >> n;	//m个对象，n对关系

	//初始化m个对象
	for (int i = 1; i <= m; i++)
		MakeSet(i);
		
	//输入n对关系
	int x, y;
	for (int i = 1; i <= n; i++){
		cin >> x >> y;
		UnionSet(x, y);
	}

	//统计连通图的个数
	for (int i = 1; i <= m; i++){
		roots[FindSet(i)] = 1;
	}
	int cnt = 0;
	for (int i = 0; i <= m; i++){
		if (roots[i])
			cnt++;
	}
	cout << "union blocks: " << cnt << endl;

	//判断两个对象是否连通（有直接或间接关系）
	cin >> x >> y;
	if (FindSet(x) == FindSet(y))
		cout << "Connected" << endl;
	else
		cout << "Not connected" << endl;

	system("pause");
}