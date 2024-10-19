#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int result;
int map[100][100];
bool check[100][100];

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };


int checkCheese()
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 1)
			{
				count++;
			}
			check[i][j] = false;
		}
	}
	return count;
}



void bfs()
{
	queue<pair<int, int>> que; // y,x
	queue<pair<int, int>> queCheese;

	que.push(make_pair(0, 0));
	check[0][0] = true;

	while (!que.empty())
	{
		int y = que.front().first;
		int x = que.front().second;
		que.pop();

		for (int ii = 0; ii < 4; ii++)
		{
			int nextY = y + dy[ii];
			int nextX = x + dx[ii];

			
			if (nextY >= 0 && nextX >= 0 && nextY < n && nextX < m)
			{
				if (check[nextY][nextX] == false)
				{
					if (map[nextY][nextX] == 0)
					{
						que.push(make_pair(nextY, nextX)); //BFS 이동
						check[nextY][nextX] = true;
					}
					else // 치즈인경우
					{
						queCheese.push(make_pair(nextY, nextX)); // 저장해놓음
						check[nextY][nextX] = true;
					}
				}
			}

		}
	}


	result = queCheese.size(); // 최외곽 치즈 개수

	for (int i = 0; i < result; i++)
	{
		int a = queCheese.front().first;
		int b = queCheese.front().second;
		map[a][b] = 0; // 최외곽 치즈를 삭제한다.
		queCheese.pop();

	}
}



int main()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}

	int timecheck = 0;
	while (1)
	{
		
		int count = checkCheese();

		if (count == 0)
		{
			break;
		}
		else
		{
			bfs();
			timecheck++;
		}
	}

	cout << timecheck << '\n';
	cout << result;

	return 0;
}