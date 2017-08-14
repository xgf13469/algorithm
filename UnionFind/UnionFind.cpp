#include <iostream>
#include <algorithm>
using namespace std;


#define MAX 100
int father[MAX];   /* father[x]��ʾx�ĸ��ڵ�*/
int Rank[MAX];     /* Rank[x]��ʾx����*/

//����һ���µļ��ϣ�ÿһ���ӽڵ����һ����������������ĸ��ڵ�
void MakeSet(int x)
{
	father[x] = x;
	Rank[x] = 0;
}

//ͨ���ݹ����ϲ��Ҹ��ڵ㣬����ʱ�ı䵱ǰ�ڵ�ĸ��ڵ㣬ֱ��ָ����ڵ㡣
int FindSet(int x)
{
	if (x == father[x])
		return father[x];
	return FindSet(father[x]);
}

//�������ϵĺϲ��㷨
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

int main(){
	int m, n;
	cin >> n >> m;	//n������m����ϵ

	//��ʼ��n������
	for (int i = 1; i <= n; i++)
		MakeSet(i);

	//����m�Թ�ϵ
	int x, y;
	for (int i = 1; i <= m; i++){
		cin >> x >> y;
		UnionSet(x, y);
	}

	//ͳ����ͨͼ�ĸ���
	int cnt = 0;
	int roots[MAX] = { 0 };
	for (int i = 1; i <= n; i++){
		int t = FindSet(i);
		if (!roots[t]){
			roots[t] = 1;
			cnt++;
		}
	}
	cout << "union blocks: " << cnt << endl;

	//�ж����������Ƿ���ͨ����ֱ�ӻ��ӹ�ϵ��
	cin >> x >> y;
	if (FindSet(x) == FindSet(y))
		cout << "Connected" << endl;
	else
		cout << "Not connected" << endl;

	system("pause");
}