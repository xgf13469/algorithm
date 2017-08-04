#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Node
{
	int x;
	int y;
	int visitType;
	Node *pre;
	Node(int _x, int _y) :x(_x), y(_y),visitType(0), pre(NULL){}
};

class Maze
{
public:
	Maze(vector<vector<int>> _maze) :maze(_maze){}
	vector<Node*> GetPath(Node &start, Node &finish);
private:
	vector<vector<int>> maze;		//��ͼ

	vector<Node*> visited;			//���汻���ʹ��Ľڵ�
	queue<Node*> frontQueue;		//ǰ����ʶ���
	queue<Node*> backQueue;		//������ʶ���
	vector<Node*> path;			//�����յ��·��

	void search(queue<Node*> &);		//���������нڵ�����ڽڵ�
	bool isValid(const Node *);			//�ڵ��Ƿ���Ч���Ƿ��ڵ�ͼ�У��Ƿ����ϰ�
	vector<Node*> GetAround(const Node *);			//��ȡָ���ڵ���Χ�Ŀ��нڵ�
	Node *isVisited(Node *);			//�жϽڵ��Ƿ񱻷��ʹ����Ƿ��ظýڵ㣬�񷵻�NULL
};

vector<Node*> Maze::GetPath(Node &start, Node &finish)
{
	start.visitType = 1;
	finish.visitType = 2;

	frontQueue.push(&start);
	backQueue.push(&finish);

	visited.push_back(&start);
	visited.push_back(&finish);

	while (!frontQueue.empty() && !backQueue.empty())
	{
		if (frontQueue.size() < backQueue.size())
			search(frontQueue);		//ǰ������
		else
			search(backQueue);		//��������

		if (!path.empty())
			break;
	}
	return path;
}

void Maze::search(queue<Node*> &que)
{
	int n = que.size();		//���������ε����нڵ�
	for (int i = 0; i < n; i++)
	{
		Node *cur = que.front();		//�Ӷ����е�����ǰ�����ĵ�
		que.pop();

		vector<Node*> around = GetAround(cur);		//�����ڵ���Χ���еĽڵ�

		for (auto &node : around)
		{
			if (node->visitType==cur->visitType)
				continue;
			else if (node->visitType==0)
			{
				node->visitType=cur->visitType;
				node->pre = cur;
				que.push(node);
				visited.push_back(node);
			}

			//��һ��������ʹ��Ľڵ��뵱ǰ�ڵ�����
			else
			{
				//cur �� node Ϊ������������ڽڵ�
				if (cur->visitType == 2)
					swap(cur, node);

				//����·��
				while (cur)
				{
					path.insert(path.begin(), cur);
					cur = cur->pre;
				}
				while (node)
				{
					path.push_back(node);
					node = node->pre;
				}
				return;
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