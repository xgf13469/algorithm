#include <iostream>
#include <algorithm>

using namespace std;

//背包问题：0-1背包与完全背包
int w[200];	//物品重量
int v[200];	//物品价值
int x[200];	//物品选中结果
int V[200][200];	//最大价值:V[i][j]表示容量为j 、物品数为i+1时背包最大价值

class Backpack
{
public:
	void solve(int n, int C)
	{
		for (int i = 0; i <= n; ++i)
			V[i][0] = 0;
		
		for (int j = 0; j <= C; ++j)
			V[0][j] = 0;
		
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= C; ++j)
			{
				int nCount = j / w[i] ? 1 : 0;		//0-1背包时
				//int nCount = j / w[i];	//完全背包时
				for (int k = 0; k <= nCount; k++)
					V[i][j] = max(V[i][j], V[i - 1][j - k*w[i]] + k*v[i]);
			}
		}

		int j = C;
		for (int i = n ; i > 0; --i)
		{
			x[i] = 0;
			while (V[i][j] > V[i-1][j])
			{
				x[i]++;
				j = j - w[i];
			}
		}

		//输出选择物品
		cout << "max value: " << V[n][C] << endl;
		cout << "select goods: ";
		for (int i = 1; i <= n; ++i)
		{
			while (x[i]-- != 0)
				cout << i << endl;
		}
	}
};

int main()
{
	int n, C;
	
	cout << "input n and C : ";		//物品数和背包容量
	cin >> n >> C;
	for (int i = 1; i <= n; ++i)
	{
		cout << "input goods " << i << "weight and value: ";		//物品重量和价值
		cin >> w[i] >> v[i];
	}
	Backpack b;
	b.solve(n, C);
	
	return 0;
}