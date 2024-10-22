#include <string>
#include <vector>
#include <queue>

using namespace std;

//문제 설명이 빈약하다.. 아래를 추가적으로 알자
//모든 트럭의 길이는.. 1이다.
//모든 트럭은 1초에 1씩 움직인다..
//1초 단위로 로직이 동작하므로 다리에 걸치는 상황은 무시된다.
//truck_weight의 순서를 섞을 필요는 없다..
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int tick = 1; // 시간
    
    queue<pair<int, int>> que; // 무게, 진입 시간
    
    // 1초 부터 시작
    que.push({truck_weights[0], tick});
    
    int curWeight = truck_weights[0]; // 현재 다리 위 트럭의 무게 총합
    int index = 1; // 다리에 진입 예정인 트럭 인덱스
    
    // 1초 단위의 while 문
    while(!que.empty()) {
        
        int frontTruckWeight = que.front().first;
        int frontTruckTime = que.front().second;
        
        // 트럭 탈출, 일차선 이므로 하나만 탈출
        // 현재시간 - 진입시간 == 다리길이 되는 순간 탈출이다.
        if(tick - frontTruckTime >= bridge_length) { 
            que.pop();
            curWeight -= frontTruckWeight;
        }
        
        // 트럭 진입 조건 체크와 트럭 진입, 일차선 이므로 하나만 진입
        if(index < truck_weights.size()) {
            if(curWeight + truck_weights[index] <= weight) {
                que.push({truck_weights[index], tick});
                curWeight += truck_weights[index];
                index++;
            }
        }
        
        // 시간 증가
        tick++;
    }
    
    return tick - 1;
}