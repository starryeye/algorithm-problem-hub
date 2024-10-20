#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct pos
{
	int y, x, tick;
};

int map[101][101];
bool check[101][101];

int n;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int flag = 0;

void dfs(pos p)
{
	check[p.y][p.x] = true;
	map[p.y][p.x] = flag;

	for (int i= 0; i < 4; i++)
	{
		int y = p.y + dy[i];
		int x = p.x + dx[i];
		
		if (y <0 || y >n - 1 || x <0 || x >n - 1)
			continue;
		if (check[y][x] == true)
			continue;
		if (map[y][x] == -1)
		{
			dfs({ y, x, 0 });
		}
		
	}
}

int bfs(int flag)
{
	queue<pos> que;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] == flag)
			{
				check[i][j] = true;

				que.push({ i, j, 0 });
			}
		}
	}
	int result = 0;

	while (!que.empty())
	{

		int quesize = que.size();

		for (int i = 0; i < quesize; i++)
		{
			pos tmp = que.front();
			que.pop();

			for (int ii = 0; ii < 4; ii++)
			{
				int y = tmp.y + dy[ii];
				int x = tmp.x + dx[ii];

				if (y <0 || y >n - 1 || x <0 || x >n - 1)
					continue;
				if (check[y][x] == true)
					continue;

				if (map[y][x] != flag && map[y][x] != 0)
				{//다른 대륙 도착
					return result;
				}

				if (map[y][x] == 0)
				{
					que.push({ y, x, tmp.tick + 1 });
					check[y][x] = true;
				}
			}
		}
		result+=1;

	}

	return result;

	
}

int main()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int s;
			cin >> s;
			if (s == 1)
				map[i][j] = -1;
			else
				map[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] == -1 && check[i][j] == false)
			{
				flag += 1; //대륙 구분 마크 1, 2, 3 ,...
				dfs({ i,j,0 });
			}
		}
	}

	

	int result = 202; // max값

	for (int i = 1; i < flag; i++)
	{
		memset(check, false, sizeof(check));
		result = min(result, bfs(i));
	}


	cout << result;


	return 0;
}