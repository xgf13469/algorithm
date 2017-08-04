#include <vector>
#include <queue>
#include <iostream>

using namespace std;

/*
���� BFS �����Թ�·��
*/

struct Node
{
	int x;		//����
	int y;
	int visitType;		//�������ͣ�0δ�����ʣ�1������
	Node *pre;		//��ǰ�ڵ��ǰһ���ڵ�
	Node(int _x, int _y) :x(_x), y(_y),visitType(0), pre(NULL){}
};
class Maze
{
public:
	Maze(vector<vector<int>> _maze) :maze(_maze){}
	vector<Node*> GetPath(Node &start, Node &finish);		//��õ����յ��·��
private:
	vector<vector<int>> maze;		//��ͼ
	vector<Node*> visited;			//���汻���ʹ��Ľڵ�
	queue<Node*> frontQueue;		//ǰ����ʶ���
	vector<Node*> path;			//�����յ��·��

	vector<Node*> GetAround(const Node *);		//��ȡָ���ڵ���Χ�Ŀ��нڵ�
	bool isValid(const Node *);		//�ڵ������
	Node *isVisited(Node *);		//�Ƿ񱻷��ʹ����Ƿ��ظýڵ㣬�񷵻�NULL
};

vector<Node*> Maze::GetPath(Node &start, Node &finish)
{
	start.visitType = 1;
	frontQueue.push(&start);
	visited.push_back(&start);

	while (!frontQueue.empty())
	{
		int n = frontQueue.size();		//���������ε����нڵ�
		for (int i = 0; i < n; i++)
		{
			Node *cur = frontQueue.front();		//�Ӷ����е�����ǰ�����ĵ�
			frontQueue.pop();

			vector<Node*> around = GetAround(cur);		//�����ڵ���Χ���еĽڵ�

			for (auto &node : around)
			{
				//�Ƿ񵽴��յ�
				if (node->x == finish.x && node->y == finish.y)
				{
					//����·��
					path.push_back(node);
					while (cur)
					{
						path.insert(path.begin(), cur);
						cur = cur->pre;
					}
				}
				else if (!node->visitType)
				{
					//���ýڵ�Ϊ�ѷ��ʣ���ǰһ���ڵ�
					node->visitType = 1;
					node->pre = cur;
					frontQueue.push(node);
					visited.push_back(node);
				}
			}
		}
		if (!path.empty())
			break;
	}
	return path;
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
		{ 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1 },
		{ 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
		{ 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0 },
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