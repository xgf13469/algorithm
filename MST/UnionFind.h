#define MAX 100
int father[MAX];   /* father[x]��ʾx�ĸ��ڵ�*/
int Rank[MAX];     /* Rank[x]��ʾx����*/

//����һ���µļ���
void MakeSet(int x)
{
	father[x] = x;
	Rank[x] = 0;
}
//ͨ���ݹ����ϲ��Ҹ��ڵ㡣
int FindSet(int x)
{
	if (x == father[x])
		return father[x];
	return FindSet(father[x]);
}
//�ϲ���������
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