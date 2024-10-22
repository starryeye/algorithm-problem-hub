#include <string>
#include <vector>

using namespace std;

int n = 0;

void dfs(int start, vector<int> adj[], vector<bool>& check) {
    
    check[start] = true;
    
    for(int i=0; i<adj[start].size(); i++) {
        
        int next = adj[start][i];
        
        if(check[next] == true)
            continue;
        
        dfs(next, adj, check);
    }
}

int solution(int n, vector<vector<int>> computers) {
    
    int answer = 0;
    
    n = computers.size();
    
    if(n == 0)
        return 0;
    
    vector<int> adj[n];
    vector<bool> check(n, false);
    
    //adj 생성
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<n; j++) {
            
            if(i == j)
                continue;
            
            if(computers[i][j])
                adj[i].push_back(j);          
        }
    }
    
    for(int i = 0; i<n; i++) {
        
        if(check[i] == false) {
            dfs(i, adj, check);
            answer++;
        }
    }
    
    return answer;
}