#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Node
{
	int x;
	int y;
	Node *pre;
	Node(int _x, int _y) :x(_x), y(_y),pre(NULL){}
};
class Maze
{
public:
	Maze(vector<vector<int>> _maze) :maze(_maze),visit(vector<vector<int>>(_maze.size(),vector<int>(_maze.size(),0))), found(false),step(0){}
	vector<Node*> GetPath(Node &start, Node &finish);
private:
	vector<vector<int>> maze;		//��ͼ
	vector<vector<int>> visit;
	bool found;		//�ҵ�·����ʶ
	int step;		//����

	vector<Node*> visited;
	queue<Node*> frontQueue;		//ǰ����ʶ���
	queue<Node*> backQueue;		//������ʶ���
	
	//˫����չ
	void search(queue<Node*> &);
	//�ڵ������
	bool isValid(const Node *);
	//��ȡָ���ڵ���Χ�Ŀ��нڵ�
	vector<Node*> GetAround(const Node *);
	Node *isVisited(Node *);
};

vector<Node*> Maze::GetPath(Node &start, Node &finish)
{
	visit[start.x][start.y] = 1;
	visit[finish.x][finish.y] = 2;
	frontQueue.push(&start);
	backQueue.push(&finish);

	visited.push_back(&start);
	visited.push_back(&finish);
	vector<Node*> path;

	while (!frontQueue.empty() || !backQueue.empty())
	{
		if (!frontQueue.empty() && (frontQueue.size() < backQueue.size()))
			search(frontQueue);		//��չǰ����������
		else
			search(backQueue);		//��չ������������

		if (found)
		{
			Node *p=visited.back();
			while(p)
			{
				path.push_back(p);
				p=p->pre;
			}
			visited.pop_back();
			p=visited.back();
			while(p)
			{
				path.insert(path.begin(),p);
				p=p->pre;
			}	
			return path;
		}
			
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
			if (visit[node->x][node->y] == visit[cur->x][cur->y])
				continue;
			else if (visit[node->x][node->y] == 0)
			{
				visit[node->x][node->y] = visit[cur->x][cur->y];
				node->pre=cur;
				que.push(node);
				visited.push_back(node);
			}
			else
			{
				visited.push_back(node);
				visited.push_back(cur);
				found = true;
				return;
			}
		}
	}
	step++;		//ÿ����һ����Σ�������1
}
bool Maze::isValid(const Node *node)
{
	if (node->x<0 || node->x > maze.size() - 1 || node->y<0 || node->y > maze.size() - 1
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
		Node *temp =new Node(node->x + d[i][0], node->y + d[i][1]);
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
	int maze[5][5] = 
	{
		{ 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 1, 0 },
	};

	vector<vector<int>> a(5,vector<int>(5));
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			a[i][j]=maze[i][j];

	Node start(0, 0);
	Node finish(4, 4);
	Maze m(a);
	
	auto path=m.GetPath(start,finish);
	for(auto node : path)
	{
		cout << "(" << node->x<<","<<node->y<<")"<<endl;
		node=node->pre;
	}
	system("pause");
	return 0;
}