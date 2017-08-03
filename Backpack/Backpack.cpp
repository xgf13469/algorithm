#include <iostream>
#include <algorithm>

using namespace std;

//�������⣺0-1��������ȫ����
int w[200];	//��Ʒ����
int v[200];	//��Ʒ��ֵ
int x[200];	//��Ʒѡ�н��
int V[200][200];	//����ֵ:V[i][j]��ʾ����Ϊj ����Ʒ��Ϊi+1ʱ��������ֵ

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
				int nCount = j / w[i] ? 1 : 0;		//0-1����ʱ
				//int nCount = j / w[i];	//��ȫ����ʱ
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

		//���ѡ����Ʒ
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
	
	cout << "input n and C : ";		//��Ʒ���ͱ�������
	cin >> n >> C;
	for (int i = 1; i <= n; ++i)
	{
		cout << "input goods " << i << "weight and value: ";		//��Ʒ�����ͼ�ֵ
		cin >> w[i] >> v[i];
	}
	Backpack b;
	b.solve(n, C);
	
	return 0;
}