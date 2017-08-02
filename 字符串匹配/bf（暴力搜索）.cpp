#include <string>
#include <iostream>
using namespace std;


//Brute force ±©Á¦ËÑË÷
int bf(const string &src, const string &pstr)
{
	int i = 0, j = 0;

	for (; i < src.size(); ++i)
	{
		if (src[i] == pstr[j])
			++j;
		else
		{
			i -= j;
			j = 0;
		}
		if (j == pstr.size())
			return i - j + 1;
	}
	return -1;
}

int main()
{
	string s("BBC ABCDAB ABCDABCDABDE");
	string p("ABCDABD");
	
	cout << "bf: " << bf(s, p) << endl;

	system("pause");
	return 0;
}