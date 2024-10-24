#include <string>
#include <vector>

using namespace std;

// 첫 번째 집을 터는 경우: 첫 번째 집을 털고 마지막 집을 털 수 없음
//      이 경우, 배열의 0번째 집부터 n-2번째 집까지 고려
// 첫 번째 집을 털지 않는 경우: 첫 번째 집을 털지 않으면 
//      두 번째 집부터 마지막 집까지를 고려할 수 있음
//
// 각 경우에 대해 독립적으로 최대 금액을 계산한 후, 두 경우 중 더 큰 값을 결과로 선택

int rob(vector<int>& money, int start, int end) {
    
    int n = end - start + 1;
    
    if (n == 0) 
        return 0;
    if (n == 1) 
        return money[start];
    
    vector<int> dp(n);
    
    // 초기화
    dp[0] = money[start];
    dp[1] = max(money[start], money[start + 1]);
    
    
    for (int i = 2; i < n; ++i) {
        // dp[i - 1] 을 선택하면, dp[i] 집은 스킵한다는 의미
        // dp[i - 2] + money[start + i] 를 선택하면, dp[i - 1] 집을 스킵한다는 의미
        dp[i] = max(dp[i - 1], dp[i - 2] + money[start + i]);
    }
    
    return dp[n - 1];
}

int solution(vector<int> money) {
    
    int n = money.size();
    
    if (n == 1) 
        return money[0];
    
    // 첫번째 집을 터는 경우와 안터는 경우로 독립적으로 계산
    int answer = max(rob(money, 0, n - 2), rob(money, 1, n - 1));
    
    return answer;
}