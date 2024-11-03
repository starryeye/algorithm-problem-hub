#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    
    int N, K;
    cin >> N >> K;

    vector<int> item_weight(N);
    vector<int> item_value(N);
    for (int i = 0; i < N; i++) {
        cin >> item_weight[i] >> item_value[i];
    }
    
    // dp[i][k] 
    //     상태 : i index 까지 고려, k 까지 제한 (용량)
    //     값 : 최대 값 (가치)
    vector<vector<int>> dp(N, vector<int>(K + 1, 0)); // 0으로 초기화
    
    // 초기화: 0 index item 을 선택할 수 있는 경우 초기값 설정
    // 선택하지 못하면, 이미 초기화된 0 이다.
    for (int w = 0; w <= K; w++) {
        if (item_weight[0] <= w) {
            dp[0][w] = item_value[0];
        }
    }

    for (int i = 1; i < N; i++) {
        for (int w = 0; w <= K; w++) {
            if (item_weight[i] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - item_weight[i]] + item_value[i]);
                // dp[i - 1][w] : i index item 선택하지 않음
                // dp[i - 1][w - item_weight[i]] + item_value[i] : i index item 선택함
            } else {
                dp[i][w] = dp[i - 1][w];
                // i index item 선택할 수 없음
            }
        }
    }

    cout << dp[N - 1][K] << endl;
    return 0;
}
