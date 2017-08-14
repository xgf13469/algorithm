#define MAX 100
int father[MAX];   /* father[x]表示x的父节点*/
int Rank[MAX];     /* Rank[x]表示x的秩*/

//建立一个新的集合
void MakeSet(int x)
{
	father[x] = x;
	Rank[x] = 0;
}
//通过递归向上查找根节点。
int FindSet(int x)
{
	if (x == father[x])
		return father[x];
	return FindSet(father[x]);
}
//合并两个集合
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