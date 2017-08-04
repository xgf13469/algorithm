#include <vector>
#include <queue>
#include <iostream>

using namespace std;

/*
�Թ�����
��������ﵽ�Թ����ڵ����·�����ȣ��������̵�·����������
*/

struct Node
{
	int x;
	int y;
	Node(int _x, int _y) :x(_x), y(_y){}
};
class Maze
{
public:
	Maze(vector<vector<int>> _maze) :maze(_maze),visit(vector<vector<int>>(_maze.size(),vector<int>(_maze.size(),0))), found(false),step(0){}
	int GetPath(Node &start, Node &finish);
private:
	vector<vector<int>> maze;		//��ͼ
	vector<vector<int>> visit;
	bool found;		//�ҵ�·����ʶ
	int step;		//����
	queue<Node> frontQueue;		//ǰ����ʶ���
	queue<Node> backQueue;		//������ʶ���
	
	//˫����չ
	void search(queue<Node> &);
	//�ڵ������
	bool isValid(const Node &);
	//��ȡָ���ڵ���Χ�Ŀ��нڵ�
	vector<Node> GetAround(const Node &);
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
			search(frontQueue);		//��չǰ����������
		else
			search(backQueue);		//��չ������������

		if (found)
			return step + 1;
	}
	return -1;
}

void Maze::search(queue<Node> &que)
{
	int n = que.size();		//���������ε����нڵ�
	for (int i = 0; i < n; i++)
	{
		Node cur = que.front();		//�Ӷ����е�����ǰ�����ĵ�
		que.pop();
		vector<Node> around = GetAround(cur);		//�����ڵ���Χ���еĽڵ�

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
	step++;		//ÿ����һ����Σ�������1
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
	int d[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };	//�������ҵĵ�

	vector<Node> around;
	for (int i = 0; i < 4; i++)
	{
		int newx = node.x + d[i][0];
		int newy = node.y + d[i][1];
		if (isValid(Node(newx, newy)))
			around.push_back(Node(node.x + d[i][0], node.y + d[i][1]));
	}
		
	return around;
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