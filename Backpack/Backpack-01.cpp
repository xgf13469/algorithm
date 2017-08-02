#include <iostream>
#include <algorithm>

using namespace std;

//0-1��������
int w[200];	//��Ʒ����
int v[200];	//��Ʒ��ֵ
int x[200];	//��Ʒѡ�н��
int V[200][200];	//����ֵ

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
	
	cout << "input n and C : ";		//��Ʒ���ͱ�������
	cin >> n >> C;
	for (int i = 0; i < n; ++i)
	{
		cout << "input goods " << i << "weight and value: ";		//��Ʒ�����ͼ�ֵ
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