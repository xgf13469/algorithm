#include <vector>
#include <stack>
#include <iostream>

using namespace std;

struct Node
{
	int x;
	int y;
	int visitType;
	Node *pre;
	Node(int _x, int _y) :x(_x), y(_y), visitType(0), pre(NULL){}
};

class Maze
{
public:
	Maze(vector<vector<int>> _maze) :maze(_maze){}
	vector<Node*> GetPath(Node &start, Node &finish);
private:
	vector<vector<int>> maze;		//��ͼ
	stack<Node *> Stack;			//�ݹ��б���ÿ��ڵ�
	vector<Node*> visited;			//���汻���ʹ��Ľڵ�
	
	vector<Node*> path;			//�����յ��·��

	void DFS(Node &finish);		//���������нڵ�����ڽڵ�
	bool isValid(const Node *);			//�ڵ��Ƿ���Ч���Ƿ��ڵ�ͼ�У��Ƿ����ϰ�
	vector<Node*> GetAround(const Node *);			//��ȡָ���ڵ���Χ�Ŀ��нڵ�
	Node *isVisited(Node *);			//�жϽڵ��Ƿ񱻷��ʹ����Ƿ��ظýڵ㣬�񷵻�NULL
};

vector<Node*> Maze::GetPath(Node &start, Node &finish)
{
	start.visitType = 1;
	Stack.push(&start);
	visited.push_back(&start);

	DFS(finish);

	return path;
}

void Maze::DFS(Node &finish)
{
	Node *cur = Stack.top();
	if (cur->x == finish.x && cur->y == finish.y)		
	{
		//��ǰ�ڵ����յ����ʱ������·��������
		while (cur)
		{
			path.insert(path.begin(),cur);
			cur = cur->pre;
		}
		return;
	}
	auto around = GetAround(cur);		//��ȡ��ǰ�ڵ�����ڽڵ�
	for (auto &node : around)
	{
		//��ÿ�����ڽڵ㣺���ñ�־������ջ�У�Ȼ��ݹ�
		if (!node->visitType)
		{
			node->visitType = 1;
			node->pre = cur;
			Stack.push(node);
			visited.push_back(node);

			DFS(finish);

			//�������ʱ�ҵ�·����path��Ϊ�գ����򷵻أ����δ�ҵ��������ոռ���Ľڵ㣬�����ýڵ�ΪΪ���ʣ����ƻ��ݣ�
			if (!path.empty())
				return;
			else
			{
				Stack.pop();
				visited.pop_back();
				node->visitType = 0;
			}
		}
	}
}
bool Maze::isValid(const Node *node)
{
	if (node->x<0 || node->x > maze.size() - 1 || node->y<0 || node->y > maze[0].size() - 1
		|| maze[node->x][node->y])
		return false;
	return true;
}
vector<Node*> Maze::GetAround(const Node *node)
{
	int d[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };	//�������ҵĵ�

	vector<Node*> around;
	for (int i = 0; i < 4; i++)
	{
		Node *temp = new Node(node->x + d[i][0], node->y + d[i][1]);
		if (isValid(temp))
		{
			auto node = isVisited(temp);
			if (node)
				around.push_back(node);
			else
				around.push_back(temp);
		}
	}
	return around;
}
Node *Maze::isVisited(Node *node)
{
	for (auto &it : visited)
	{
		if (node->x == it->x && node->y == it->y)
			return it;
	}
	return NULL;
}

int main()
{
	vector<vector<int>> maze = {
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0 },
		{ 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }
	};

	Node start(0, 0);
	Node finish(7, 11);
	Maze m(maze);

	auto path = m.GetPath(start, finish);
	if (path.empty())
		cout << "no path!" << endl;
	for (auto node : path)
	{
		cout << "(" << node->x << "," << node->y << ")" << endl;
		node = node->pre;
	}
	system("pause");
	return 0;
}