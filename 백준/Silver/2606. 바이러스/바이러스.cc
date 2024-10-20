#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int bfs(int start, vector<vector<int>>& adj, vector<bool>& check) {
    
    int answer = 0;
	queue<int> que;

	que.push(start);
	check[start] = true;

	while (!que.empty()) {
        
		int cur = que.front();
		que.pop();

		for (int i = 0; i < adj[cur].size(); i++) {
            
			int next = adj[cur][i];

			if (check[next] == true)
				continue;

			que.push(next);
			check[next] = true;
			answer++;
		}
	}
    
    return answer;
}

int main() {
    
    int n, e;
    
	cin >> n;
	cin >> e;

    vector<vector<int>> adj(n);
    vector<bool> check(n);
    
	for (int i = 0; i < e; i++) {
        
		int a, b;
		cin >> a >> b;

        // 코드에서는 -1
		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}

	int answer = bfs(0, adj, check); // 0번 컴퓨터부터 시작 (문제에선 1번)

	cout << answer;

	return 0;
}