#include <iostream>

using namespace std;

//男生人数
#define M 5
//女生人数
#define W 4

//男生和女生之间的联系：1表示可以配对，0表示不能
int g[M][W] =
{ { 1, 1, 0, 1 },
{ 0, 1, 1, 0 },
{ 1, 0, 0, 1 },
{ 0, 0, 1, 1 },
{ 0, 1, 0, 1 } };

int girl[W];
int used[W];

//匈牙利算法
//主要解决 M 个对象（如男生）与 W 个对象（如女生）的配对问题。首先初始化他们之间的连接 g 矩阵，used 表示女生是否配对，girl 表示女生配对成功时的配对对象。

bool find(int x)
{
	//扫描每个妹子
	for (int j = 1; j <= W; j++)
	{
		//如果有暧昧并且还没有标记过
		if (g[x][j] == true && used[j] == false)
		{
			used[j] = 1;

			//名花无主或者能腾出个位置来，这里使用递归
			if (girl[j] == 0 || find(girl[j]))
			{
				girl[j] = x;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	//在主程序我们这样做：每一步相当于我们上面描述的一二三四中的一步
	int all = 0;
	for (int i = 1; i <= M; i++)
	{
		memset(used, 0, sizeof(used));    //这个在每一步中清空
		if (find(i))
			all += 1;
	}
	cout << all << endl;
	system("pause");
}

