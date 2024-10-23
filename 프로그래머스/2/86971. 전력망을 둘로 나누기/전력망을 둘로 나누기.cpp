#include <string>
#include <vector>

using namespace std;

//양분 되었는가..
bool isValid(vector<bool> check) {
    for(auto c : check) {
        if(c == false)
            return true;
    }
    
    return false;
}

//tmp : 송전탑 count
void dfs(int start, vector<int> adj[], vector<bool>& check, int& tmp) {
    
    check[start] = true;
    tmp++;
    
    for(int i = 0; i < adj[start].size(); i++) {
        int next = adj[start][i];
        
        if(check[next] == true)
            continue;
        
        dfs(next, adj, check, tmp);
    }
}

int solution(int n, vector<vector<int>> wires) {
    int answer = n;
    

    
    //전선 하나씩 끊기
    for(int t = 0; t < wires.size(); t++) {
        
        vector<int> adj[n];
        vector<bool> check(n, false);
        
        //전선 구축
        for(int i = 0; i < wires.size(); i++) {
            
            if(t == i) // 끊기
                continue;
            
            adj[wires[i][0] -1].push_back(wires[i][1] -1);
            adj[wires[i][1] -1].push_back(wires[i][0] -1);
        }
        
        int tmp = 0;
        dfs(0, adj, check, tmp);
        
        if(isValid(check) == false)
            continue;
        
        answer = min(answer, abs(n-tmp-tmp));
    }
    
    return answer;
}
/*
//?
int solution(int n, vector<vector<int>> wires) {
    vector<vector<int>> graph(n + 1);
    for(int i = 0; i < (int)wires.size(); i++) {
        int u = wires[i][0];
        int v = wires[i][1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> siz(n + 1);
    function<void(int, int)> dfs = [&](int cur, int prev)  -> void {
        siz[cur] = 1;
        for(int nxt : graph[cur]) {
            if(nxt == prev) continue;
            dfs(nxt, cur);
            siz[cur] += siz[nxt];
        }
    };
    dfs(1, -1);
    int answer = INT_MAX;
    for(int i = 1; i <= n; i++) {
        for(int j : graph[i]) {
            int l = siz[j];
            int r = n - siz[j];
            answer = min(answer, abs(l - r));
        }
    }
    return answer;
}
*/