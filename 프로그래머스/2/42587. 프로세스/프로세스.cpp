#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> priorities, int location) {
    
    int answer = 0;
    
    //priority_queue<int> pq; 와 동일하다. less 가 기본 값이며 큰게 top 이다.
    priority_queue<int, vector<int>, less<int>> pq; // 중요도 적재
    queue<pair<int, int>> q; // 중요도, 인덱스
        
    for (int i = 0; i < priorities.size(); i++) {
        pq.push(priorities[i]);
        q.push({priorities[i], i});
    }
    
    while (!q.empty()) {
        auto process = q.front();
        q.pop();
        
        if (pq.top() != process.first) {
            // 우선순위에 맞지 않는 프로세스이면 그대로 큐에 집어 넣는다.
            q.push(process);
        } else {
            // 우선순위에 맞는 프로세스로 꺼낸다(실행한다.)
            answer++;
            pq.pop(); // 우선순위에서도 제거
            if (location == process.second) { // 정답
                return answer;
            }
        }
    }
    
    return answer;
}