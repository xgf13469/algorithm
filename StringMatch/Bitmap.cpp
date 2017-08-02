#include <string>
#include <iostream>
using namespace std;

//BitapÀ„∑®
int bitap(const string &src, const string &pstr)
{
	int plen = pstr.size();
	char map[CHAR_MAX];
	memset(map, 0, CHAR_MAX);

	map[0] = 1;
	for (int i = 0; i < src.size(); i++)
	{
		for (int j = plen - 1; j >= 0; j--)
		{
			map[j + 1] = map[j] & (src[i] == pstr[j]);
		}

		if (map[plen] == 1)
		{
			return i - plen + 1;
		}
	}
	return -1;
}

int main()
{
	string s("BBC ABCDAB ABCDABCDABDE");
	string p("DAB");
	
	cout << "bitmap: " << bitap(s, p) << endl;
	system("pause");
	return 0;
}