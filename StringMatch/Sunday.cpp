#include <string>
#include <iostream>
using namespace std;

//sunday Ëã·¨
#define CHAR_MAX 256
int sunday(const string &src, const string &pstr)
{

	int map[CHAR_MAX];
	int j;
	int plen = pstr.size();

	//preprocess
	for (j = 0; j < CHAR_MAX; j++)
		map[j] = plen;
	for (j = 0; j < plen; j++)
		map[pstr[j]] = plen - j-1;

	//match process
	int i=0;
	j = 0;

	for (; i < src.size(); ++i)
	{
		if (src[i] == pstr[j])
			++j;
		else
		{
			i += map[src[i + plen]];
			j = 0;
		}
		if (j == plen)
			return i - j + 1;
	}
	return -1;
}


int main()
{
	string s("BBC ABCDAB ABCDABCDABDE");
	string p("ABCDABD");
	
	cout << "sunday: " << sunday(s, p) << endl;
	system("pause");
	return 0;
}