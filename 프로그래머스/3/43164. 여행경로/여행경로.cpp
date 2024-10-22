#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void dfs(string airport, vector<string>& path, map<string, vector<string>>& routes, vector<string>& answer, int ticketNum) {
    
    // 현재 경로에 공항 추가
    path.push_back(airport);

    // 모든 티켓을 사용했으면 결과 검토
    if (path.size() == ticketNum + 1) {
        if (answer.empty() || path < answer) { // 각원소를 비교하며 사전순으로 빠른지 비교
            answer = path;
        }
        path.pop_back();
        return;
    }

    // 현재 공항에서 갈 수 있는 다음 공항 탐색
    for (int i = 0; i < routes[airport].size(); i++) {
        
        string next = routes[airport][i];
        
        // 임시로 제거 (항공권 사용)
        routes[airport].erase(routes[airport].begin() + i); // i 번째 원소 삭제
        
        dfs(next, path, routes, answer, ticketNum);
        
        // 임시로 제거한 티켓 복원 백트래킹(복원)
        routes[airport].insert(routes[airport].begin() + i, next); // i 번째에 원소 추가
    }

    path.pop_back();
}

vector<string> solution(vector<vector<string>> tickets) {
    
    vector<string> answer;
    
    // 출발지 사전순 정렬됨 -> map
    map<string, vector<string>> routes; // 출발지, 목적지리스트
    
    for (auto& ticket : tickets) {
        routes[ticket[0]].push_back(ticket[1]);
    }
    
    // 목적지리스트 사전순 정렬, less 가 디폴트
    for (auto& route : routes) {
        sort(route.second.begin(), route.second.end(), less<string>());
    }

    vector<string> path;
    
    dfs("ICN", path, routes, answer, tickets.size());
    
    return answer;
}


/*
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
} */