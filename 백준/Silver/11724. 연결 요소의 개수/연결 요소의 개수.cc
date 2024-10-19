#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<bool>& check) {
    
	check[node] = true;

	for (int i = 0; i < adj[node].size(); i++) {
		
        int next = adj[node][i];

		if (check[next] == false) {
			dfs(next, adj, check);
		}
	}
}


int main() {
    
	int n, m;

	cin >> n >> m;
    
    vector<vector<int>> adj(n);
    vector<bool> check(n, false);

	for (int i = 0; i < m; i++) {
		int u, v;

		cin >> u >> v;
        
        // 문제에서는 1부터 시작하지만, 코드상에선 0부터로 하겠다.
        u--;
        v--;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int count = 0;

	for (int i = 0; i < n; i++) {
        
		if (check[i] == false) {
			dfs(i, adj, check);
			count++;
		}
	}

	cout << count; // 연결요소의 개수란.. 섬(서로 연결된 그래프가 아님)의 갯수이다.

	return 0;
}