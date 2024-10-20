#include <iostream>
//#include <cstring> // memset
#include <vector>
using namespace std;


void dfs(int start, int K, vector<vector<pair<int, int>>>& adj, vector<bool>& check, int& answer) {
    
	check[start] = true;

	for (int i = 0; i < adj[start].size(); i++) {
        
		int next = adj[start][i].first;
		int recommend = adj[start][i].second;

		if (check[next] == true || K > recommend)
			continue;

		dfs(next, K, adj, check, answer);
		answer++;
	}
}


int main() {
    
    int N, Q;
	cin >> N >> Q;

    vector<vector<pair<int, int>>> adj(N);
    vector<bool> check(N, false);
    
	for (int i = 0; i < N - 1; i++) {
        
		int p, q, r;

		cin >> p >> q >> r;

		adj[p - 1].push_back(make_pair(q - 1, r));
		adj[q - 1].push_back(make_pair(p - 1, r));
	}

	for (int i = 0; i < Q; i++) {
        
        int K; // 기준 점수
		int v; // 스타트 영상
		cin >> K >> v;

        int answer = 0;
        dfs(v - 1, K, adj, check, answer);
		cout << answer << endl;

		// memset(check, false, sizeof(check));
        fill(check.begin(), check.end(), false);
	}
    
	return 0;
}