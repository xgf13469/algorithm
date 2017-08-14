#include<iostream>
#include<string>
#include<stack>//ջͷ�ļ�
using namespace std;
void change_bracket(string &exp);//�������ź�������ת��С���ţ�ͬʱ��������xת��0-x����ʽ
int mid_to_post(string exp);
int calculate(int a, int b, char sym);
int main()
{
	string exp;
	while (cin >> exp)
	{
		change_bracket(exp);
		int exp_post = mid_to_post(exp);
		cout << exp_post << endl;
	}
	return 0;
}
//�Ѵ����ź������Ż���С���ţ��Ա���ٺ��ڹ�����ж�
void change_bracket(string &exp)
{
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == '{' || exp[i] == '[')
			exp[i] = '(';
		if (exp[i] == '}' || exp[i] == ']')
			exp[i] = ')';
	}
}
int mid_to_post(string exp)
{
	int flag = 0;//�����ű�־��0Ϊ�������ţ�1Ϊ���ţ�2Ϊ����
	stack<int> exp_post;//����ջ
	stack<char> symbol;//����ջ
	for (int i = 0; i < exp.size(); i++)
	{
		char temp;
		if (isdigit(exp[i]))//Ϊ����ʱ
		{
			int j = i, num = 0;
			while (i + 1 < exp.length() && isdigit(exp[i + 1])) i++;
			string str_num = exp.substr(j, i - j + 1);
			for (int k = 0; k < str_num.size(); k++)
				num = num * 10 + str_num[k] - '0';
			if (flag == 2)
				num = 0 - num;
			flag = 0;
			exp_post.push(num);
		}
		else if (exp[i] == '*' || exp[i] == '/' || exp[i] == '(')//Ϊ�˳�ʱ
			symbol.push(exp[i]);
		else if (exp[i] == '+' || exp[i] == '-')//Ϊ�Ӽ�ʱ
		{
			/*��������*/
			if (!i || exp[i - 1] == '(')
				if (exp[i] == '+')
					flag = 1;
				else
					flag = 2;

			/*��������_end*/
			while (!flag&&!symbol.empty() && symbol.top() != '(')//��ջ�ǿ�ʱ������ջ�������ţ����������ջ���� 
			{
				int b = 0, a = 0;
				char sym_temp;
				b = exp_post.top();
				exp_post.pop();
				a = exp_post.top();
				exp_post.pop();
				sym_temp = symbol.top();
				symbol.pop();
				exp_post.push(calculate(a, b, sym_temp));//��������ջ
			}
			if (!flag) symbol.push(exp[i]);
		}
		else if (exp[i] == ')')//Ϊ������ʱ
		{
			while (symbol.top() != '(')
			{
				int b = 0, a = 0;
				char sym_temp;
				b = exp_post.top();
				exp_post.pop();
				a = exp_post.top();
				exp_post.pop();
				sym_temp = symbol.top();
				symbol.pop();
				exp_post.push(calculate(a, b, sym_temp));//��������ջ
			}
			symbol.pop();
		}
		else
			cout << "Input error!!!" << endl;
	}
	//ѭ���������ʣ�µķ��ŵ��������������ջ����
	while (!symbol.empty())
	{
		int b = 0, a = 0;
		char sym_temp;
		b = exp_post.top();
		exp_post.pop();
		a = exp_post.top();
		exp_post.pop();
		sym_temp = symbol.top();
		symbol.pop();
		exp_post.push(calculate(a, b, sym_temp));//��������ջ
	}
	return exp_post.top();
}

int calculate(int a, int b, char sym)
{
	switch (sym)
	{
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	default:
		return 0;
		break;
	}
}
