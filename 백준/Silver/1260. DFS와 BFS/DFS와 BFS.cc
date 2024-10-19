#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<bool>& check) {
	
    check[node] = true;
	cout << node << " ";

	for (int i = 0; i < adj[node].size(); i++) {
		int next = adj[node][i];
        
		if (check[next] == false) {
			dfs(next, adj, check);
		}
	}
}

void bfs(int start, vector<vector<int>>& adj, vector<bool>& check) {
    
	queue<int> que;

	check[start] = true;
	que.push(start);

	while (!que.empty()) {
        
		int node = que.front();
		que.pop();

		cout << node << " ";

		for (int i = 0; i < adj[node].size(); i++) {
            
			int next = adj[node][i];
            
			if (check[next] == false) {
				check[next] = true;
				que.push(next);
			}
		}
	}
}


int main() {
    
	int n, m, start;
    
    vector<vector<int>> adj(1001);
    vector<bool> check(1001, false);
    
	cin >> n >> m >> start;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for (int i = 0; i <= n; i++) {
		sort(adj[i].begin(), adj[i].end());
	}
	
    dfs(start, adj, check);
	
    cout << endl;
	
    fill(check.begin(), check.end(), false);
	bfs(start, adj, check);

	return 0;
}