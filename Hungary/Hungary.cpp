#include <iostream>

using namespace std;

//��������
#define M 5
//Ů������
#define W 4

//������Ů��֮�����ϵ��1��ʾ������ԣ�0��ʾ����
int g[M][W] =
{ { 1, 1, 0, 1 },
{ 0, 1, 1, 0 },
{ 1, 0, 0, 1 },
{ 0, 0, 1, 1 },
{ 0, 1, 0, 1 } };

int girl[W];
int used[W];

//�������㷨
//��Ҫ��� M ���������������� W ��������Ů������������⡣���ȳ�ʼ������֮������� g ����used ��ʾŮ���Ƿ���ԣ�girl ��ʾŮ����Գɹ�ʱ����Զ���

bool find(int x)
{
	//ɨ��ÿ������
	for (int j = 1; j <= W; j++)
	{
		//������������һ�û�б�ǹ�
		if (g[x][j] == true && used[j] == false)
		{
			used[j] = 1;

			//���������������ڳ���λ����������ʹ�õݹ�
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
	//��������������������ÿһ���൱����������������һ�������е�һ��
	int all = 0;
	for (int i = 1; i <= M; i++)
	{
		memset(used, 0, sizeof(used));    //�����ÿһ�������
		if (find(i))
			all += 1;
	}
	cout << all << endl;
	system("pause");
}

