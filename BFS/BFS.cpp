#include <vector>
#include <queue>
#include <iostream>

using namespace std;

/*
单向 BFS 搜索迷宫路径
*/

struct Node
{
	int x;		//坐标
	int y;
	int visitType;		//访问类型：0未被访问，1被访问
	Node *pre;		//当前节点的前一个节点
	Node(int _x, int _y) :x(_x), y(_y),visitType(0), pre(NULL){}
};
class Maze
{
public:
	Maze(vector<vector<int>> _maze) :maze(_maze){}
	vector<Node*> GetPath(Node &start, Node &finish);		//获得到达终点的路径
private:
	vector<vector<int>> maze;		//地图
	vector<Node*> visited;			//保存被访问过的节点
	queue<Node*> frontQueue;		//前向访问队列
	vector<Node*> path;			//到达终点的路径

	vector<Node*> GetAround(const Node *);		//获取指定节点周围的可行节点
	bool isValid(const Node *);		//节点可行性
	Node *isVisited(Node *);		//是否被访问过，是返回该节点，否返回NULL
};

vector<Node*> Maze::GetPath(Node &start, Node &finish)
{
	start.visitType = 1;
	frontQueue.push(&start);
	visited.push_back(&start);

	while (!frontQueue.empty())
	{
		int n = frontQueue.size();		//遍历这个层次的所有节点
		for (int i = 0; i < n; i++)
		{
			Node *cur = frontQueue.front();		//从队列中弹出当前搜索的点
			frontQueue.pop();

			vector<Node*> around = GetAround(cur);		//搜索节点周围可行的节点

			for (auto &node : around)
			{
				//是否到达终点
				if (node->x == finish.x && node->y == finish.y)
				{
					//保存路径
					path.push_back(node);
					while (cur)
					{
						path.insert(path.begin(), cur);
						cur = cur->pre;
					}
				}
				else if (!node->visitType)
				{
					//设置节点为已访问，及前一个节点
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