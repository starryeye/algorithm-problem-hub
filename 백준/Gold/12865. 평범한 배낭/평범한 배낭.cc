#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Knapsack Problem (배낭 문제)
// 제한된 용량 내에서 가장 높은 가치를 얻기 위해 선택할 수 있는 물건들을 조합하는 문제.

// 가치는 높으면 높을 수록 좋다. -> max
// 제한된 용량 -> dp[n] : n 용량까지 제한된 배낭으로 담을 수 있는 최대 가치

int main() {
    
    int N, K;  // N: 물품의 수, K: 배낭의 최대 무게
    cin >> N >> K;

    vector<int> weight(N);  // 각 물품의 무게를 저장하는 배열
    vector<int> value(N);   // 각 물품의 가치를 저장하는 배열

    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> value[i];  // 물품의 무게와 가치 입력
    }
    
    vector<int> dp(K + 1, 0); // 가치 최소값 0 으로 초기화
    dp[0] = 0; // 0 무게 제한, 최대 가치는 0
    
    
    // 각 물품에 대해 DP 테이블 갱신
    for (int i = 0; i < N; i++) {  // 모든 물품을 순회
        
        // 무게 w를 역순으로 탐색
        // 정순으로 탐색하면.. 동일한 item 을 여러번 담을 수 있다.
        for (int w = K; w >= weight[i]; w--) { // weight[i] 보다 작을땐 못담는다.
            
            // 현재 물품을 담을지 말지 결정
            dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
            // dp[w]: 현재 배낭 무게가 w일 때 최대 가치 (선택하면, 담지 않는 의미)
            // dp[w - weight[i]] + value[i]: 물품 i를 추가했을 때의 가치 (선택하면, 담는다는 의미)
        }
    }
    
    // 참고
    // N = 3, K = 5
    // item 1: 무게 = 1, 가치 = 6
    // item 2: 무게 = 2, 가치 = 10
    // item 3: 무게 = 3, 가치 = 12 일때..
    // 최초   , dp=[0,0,0,0,0,0]
    // item 1, dp=[0,6,6,6,6,6]
    // item 2, dp=[0,6,10,16,16,16]
    // item 3, dp=[0,6,10,12,18,22]
    

    // 결과 출력: 배낭 최대 무게에서의 최대 가치
    cout << dp[K] << endl;
    
    return 0;
}