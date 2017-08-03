#include <unordered_map>
#include <string>
#include <vector>
#include <set>
using namespace std;


//??????????????
class TrieTree
{
public:
	TrieTree(char _ch) :ch(_ch),isEnd(false){}		//???
	void insert(const string &);		//??????
	bool isExist(const string &s);		//?????????
	~TrieTree(){}
private:
	char ch;					//??
	unordered_map<char, TrieTree*> NextChar;	//??????????????????
	bool isEnd;					//?????

	//??????????????
	TrieTree *findNextChar(char ch_find)
	{
		auto it = NextChar.find(ch_find);
		//?????????
		if (it != NextChar.end())
			return NextChar[ch_find];
		return NULL;
	}
};

void TrieTree::insert(const string &s)
{
	TrieTree *node = this;
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		//???????????
		if (node->findNextChar(*it) != NULL)
			node = node->NextChar[*it];

		//???
		else
		{
			//????????? it ??????
			for (auto it_char = it; it_char != s.end(); ++it_char)
			{
				//?????????????????? map ?
				TrieTree *p = new TrieTree(*it_char);
				node->NextChar[*it_char] = p;
				node = p;
			}
			break;
		}
	}
	//??????????????
	node->isEnd = true;
}
bool TrieTree::isExist(const string &s)
{
	TrieTree *node = this;
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		if (node->findNextChar(*it) == NULL)
			break;
		node = node->NextChar[*it];
	}
	//????????????
	return node->isEnd;
}


//√Ù∏–¥ π˝¬À≤‚ ‘
int main()
{
	string strs[] = { "fuck", "bitch", "shit", "kill", "fuc", "fuck you", "bullshit", "killing"};
	
	TrieTree tree(' ');
	cout << "sensitive words: ";
	for (int i = 0; i < 5; ++i)
	{
		cout << strs[i] << "  ";
		tree.insert(strs[i]);
	}
	cout << endl;
	for (int i = 0; i < 8; ++i)
	{
		cout<< "\""<< strs[i] << "\""<< " is sensitive? : " <<tree.isExist(strs[i])<<endl;
	}
	getchar();
}