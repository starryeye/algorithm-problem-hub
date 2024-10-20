#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, m;
vector<int> adj[101];
bool check[101];
int ans;


int bfs(int start, int end)
{
	queue<int> que;

	check[start] = true;
	que.push(start);

	while (!que.empty())
	{
		int quesize = que.size();
		for (int a = 0; a < quesize; a++)
		{
			int node = que.front();
			que.pop();

			if (node == end)
				return ans;


			for (int i = 0; i < adj[node].size(); i++)
			{
				int next = adj[node][i];

				if (check[next] == true)
					continue;

				que.push(next);
				check[next] = true;
			}
		}
		ans++;
	}

	return -1;
}

int main()
{
	int p1, p2;
	cin >> n;

	cin >> p1 >> p2;

	cin >> m;

	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	cout << bfs(p1, p2);

	return 0;
}