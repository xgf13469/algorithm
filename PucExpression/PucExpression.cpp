#include<iostream>
#include<string>
#include<stack>//栈头文件
using namespace std;
void change_bracket(string &exp);//将大括号和中括号转成小括号，同时，将负数x转成0-x的形式
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
//把大括号和中括号换成小括号，以便减少后期过多的判断
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
	int flag = 0;//正负号标志，0为无正负号，1为正号，2为负号
	stack<int> exp_post;//数字栈
	stack<char> symbol;//符号栈
	for (int i = 0; i < exp.size(); i++)
	{
		char temp;
		if (isdigit(exp[i]))//为数字时
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
		else if (exp[i] == '*' || exp[i] == '/' || exp[i] == '(')//为乘除时
			symbol.push(exp[i]);
		else if (exp[i] == '+' || exp[i] == '-')//为加减时
		{
			/*处理负号先*/
			if (!i || exp[i - 1] == '(')
				if (exp[i] == '+')
					flag = 1;
				else
					flag = 2;

			/*处理负号先_end*/
			while (!flag&&!symbol.empty() && symbol.top() != '(')//堆栈非空时，符号栈弹出符号，并结合数字栈计算 
			{
				int b = 0, a = 0;
				char sym_temp;
				b = exp_post.top();
				exp_post.pop();
				a = exp_post.top();
				exp_post.pop();
				sym_temp = symbol.top();
				symbol.pop();
				exp_post.push(calculate(a, b, sym_temp));//计算结果入栈
			}
			if (!flag) symbol.push(exp[i]);
		}
		else if (exp[i] == ')')//为右括号时
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
				exp_post.push(calculate(a, b, sym_temp));//计算结果入栈
			}
			symbol.pop();
		}
		else
			cout << "Input error!!!" << endl;
	}
	//循环结束后把剩下的符号弹出，并结合数字栈计算
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
		exp_post.push(calculate(a, b, sym_temp));//计算结果入栈
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
