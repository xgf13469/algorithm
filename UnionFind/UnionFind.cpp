#include <iostream>
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

//���ڵ�
int roots[MAX];

int main(){
	int m,n;
	cin >> m >> n;	//m������n�Թ�ϵ

	//��ʼ��m������
	for (int i = 1; i <= m; i++)
		MakeSet(i);
		
	//����n�Թ�ϵ
	int x, y;
	for (int i = 1; i <= n; i++){
		cin >> x >> y;
		UnionSet(x, y);
	}

	//ͳ����ͨͼ�ĸ���
	for (int i = 1; i <= m; i++){
		roots[FindSet(i)] = 1;
	}
	int cnt = 0;
	for (int i = 0; i <= m; i++){
		if (roots[i])
			cnt++;
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