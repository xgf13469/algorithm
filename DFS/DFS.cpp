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
	vector<vector<int>> maze;		//地图
	stack<Node *> Stack;			//递归中保存每层节点
	vector<Node*> visited;			//保存被访问过的节点
	
	vector<Node*> path;			//到达终点的路径

	void DFS(Node &finish);		//搜索队列中节点的相邻节点
	bool isValid(const Node *);			//节点是否有效：是否在地图中；是否有障碍
	vector<Node*> GetAround(const Node *);			//获取指定节点周围的可行节点
	Node *isVisited(Node *);			//判断节点是否被访问过：是返回该节点，否返回NULL
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
		//当前节点与终点相等时，插入路径并返回
		while (cur)
		{
			path.insert(path.begin(),cur);
			cur = cur->pre;
		}
		return;
	}
	auto around = GetAround(cur);		//获取当前节点的相邻节点
	for (auto &node : around)
	{
		//对每个相邻节点：设置标志，放入栈中，然后递归
		if (!node->visitType)
		{
			node->visitType = 1;
			node->pre = cur;
			Stack.push(node);
			visited.push_back(node);

			DFS(finish);

			//如果返回时找到路径（path不为空），则返回；如果未找到，弹出刚刚加入的节点，并设置节点为为访问（类似回溯）
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