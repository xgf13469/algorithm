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
	vector<vector<int>> maze;		//地图

	vector<Node*> visited;			//保存被访问过的节点
	queue<Node*> frontQueue;		//前向访问队列
	queue<Node*> backQueue;		//反向访问队列
	vector<Node*> path;			//到达终点的路径

	void search(queue<Node*> &);		//搜索队列中节点的相邻节点
	bool isValid(const Node *);			//节点是否有效：是否在地图中；是否有障碍
	vector<Node*> GetAround(const Node *);			//获取指定节点周围的可行节点
	Node *isVisited(Node *);			//判断节点是否被访问过：是返回该节点，否返回NULL
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
			search(frontQueue);		//前向搜索
		else
			search(backQueue);		//后向搜索

		if (!path.empty())
			break;
	}
	return path;
}

void Maze::search(queue<Node*> &que)
{
	int n = que.size();		//遍历这个层次的所有节点
	for (int i = 0; i < n; i++)
	{
		Node *cur = que.front();		//从队列中弹出当前搜索的点
		que.pop();

		vector<Node*> around = GetAround(cur);		//搜索节点周围可行的节点

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

			//另一个方向访问过的节点与当前节点相邻
			else
			{
				//cur 和 node 为两个方向的相邻节点
				if (cur->visitType == 2)
					swap(cur, node);

				//保存路径
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
	int d[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };	//上下左右的点

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