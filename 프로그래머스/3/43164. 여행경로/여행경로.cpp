#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<string> solution(vector<vector<string>> tickets) {
    
    vector<string> answer;
    
    sort(tickets.begin(), tickets.end(), greater<vector<string>>());
    
    unordered_map<string, vector<string>> routes; // 출발지, 목적지리스트
    
    for(int i = 0; i < tickets.size(); i++) {
        routes[tickets[i][0]].push_back(tickets[i][1]);
    }
    
    vector<string> s = {"ICN"}; // stack(vector) 을 사용하여 dfs
    
    while(!s.empty()) {
        string tmp = s.back();
        
        if(routes.find(tmp) == routes.end() || routes[tmp].empty()) {
            answer.push_back(tmp);
            s.pop_back();
        } else {
            s.push_back(routes[tmp].back());
            routes[tmp].pop_back();
        }
    }
    
    reverse(answer.begin(), answer.end());
    
    return answer;
}