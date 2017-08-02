#include <iostream>
#include <algorithm>

using namespace std;

//0-1背包问题
int w[200];	//物品重量
int v[200];	//物品价值
int x[200];	//物品选中结果
int V[200][200];	//最大价值

class Backpack
{
public:
	void solve(int n, int C)
	{
		for (int i = 0; i <= n; ++i){
			V[i][0] = 0;
		}
		for (int j = 0; j <= C; ++j){
			V[0][j] = 0;
		}
		for (int i = 0; i < n; ++i){
			for (int j = 0; j <= C; ++j){
				if (j < w[i])
					V[i][j] = V[i - 1][j];
				else
					V[i][j] = max(V[i - 1][j], V[i - 1][j - w[i]] + v[i]);
			}
		}

		int j = C;
		for (int i = n - 1; i >= 0; --i){
			if (V[i][j]>V[i - 1][j]){
				x[i] = 1;
				j = j - w[i];
			}
			else
				x[i] = 0;
		}
	}
};

int main()
{
	int n, C;
	
	cout << "input n and C : ";		//物品数和背包容量
	cin >> n >> C;
	for (int i = 0; i < n; ++i)
	{
		cout << "input goods " << i << "weight and value: ";		//物品重量和价值
		cin >> w[i] >> v[i];
	}
	Backpack b;
	b.solve(n, C);

	cout << "max value sum : " << V[n-1][C] << endl;
	cout << "select goods: ";
	for (int i = 0; i < n; ++i)
	{
		if (x[i] != 0)
			cout << i + 1 << endl;
	}
	cout << endl;
	
	return 0;
}