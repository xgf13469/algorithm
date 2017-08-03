#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Node
{
	int x;
	int y;
	Node *next;
	Node(int _x, int _y) :x(_x), y(_y),next(NULL){}
};
class Maze
{
public:
	Maze(vector<vector<int>> _maze) :maze(_maze),visit(vector<vector<int>>(_maze.size(),vector<int>(_maze.size(),0))), found(false),step(0){}
	int GetPath(Node &start, Node &finish);
private:
	vector<vector<int>> maze;		//地图
	vector<vector<int>> visit;
	bool found;		//找到路径标识
	int step;		//步数

	vector<Node *> visited;
	queue<Node> frontQueue;		//前向访问队列
	queue<Node> backQueue;		//反向访问队列
	
	//双向扩展
	void search(queue<Node> &);
	//节点可行性
	bool isValid(const Node &);
	//获取指定节点周围的可行节点
	vector<Node> GetAround(const Node &);
	Node *isVisited(Node &);
};

int Maze::GetPath(Node &start, Node &finish)
{
	visit[start.x][start.y] = 1;
	visit[finish.x][finish.y] = 2;
	frontQueue.push(start);
	backQueue.push(finish);

	while (!frontQueue.empty() || !backQueue.empty())
	{
		if (!frontQueue.empty() && (frontQueue.size() < backQueue.size()))
			search(frontQueue);		//扩展前向搜索队列
		else
			search(backQueue);		//扩展后向搜索队列

		if (found)
			return step + 1;
	}
	return -1;
}

void Maze::search(queue<Node> &que)
{
	int n = que.size();		//遍历这个层次的所有节点
	for (int i = 0; i < n; i++)
	{
		Node cur = que.front();		//从队列中弹出当前搜索的点
		que.pop();
		vector<Node> around = GetAround(cur);		//搜索节点周围可行的节点

		for (auto &node : around)
		{
			if (visit[node.x][node.y] == visit[cur.x][cur.y])
				continue;
			else if (visit[node.x][node.y] == 0)
			{
				visit[node.x][node.y] = visit[cur.x][cur.y];
				que.push(node);
			}
			else
			{
				found = true;
				return;
			}
		}
	}
	step++;		//每遍历一个层次，步数加1
}
bool Maze::isValid(const Node &node)
{
	if (node.x<0 || node.x > maze.size() - 1 || node.y<0 || node.y > maze.size() - 1
		|| maze[node.x][node.y])
		return false;
	return true;
}
vector<Node> Maze::GetAround(const Node &node)
{
	int d[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };	//上下左右的点

	vector<Node> around;
	for (int i = 0; i < 4; i++)
	{
		Node temp(node.x + d[i][0], node.y + d[i][1]);
		if (isValid(temp))
		{
			auto node = isVisited(temp);
			if (node)
				around.push_back(*node);
			else
				around.push_back(temp);
		}
	}
	return around;
}

Node *Maze::isVisited(Node &node)
{
	for (auto &it : visited)
	{
		if (node.x == it->x && node.y == it->y)
			return it;
	}
	return NULL;
}
int main()
{
	vector<vector<int>> maze = {
		{ 0, 1, 0, 0, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 0 },
		{ 0, 0, 0, 1, 0 },
	};

	Node start(0, 0);
	Node finish(4, 4);
	Maze m(maze);
	
	cout << m.GetPath(start, finish);

	system("pause");
	return 0;
}