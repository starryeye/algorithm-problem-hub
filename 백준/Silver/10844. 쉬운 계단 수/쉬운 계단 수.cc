#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    // dp[n] : 길이가 n 인 계단수 총 갯수
    
    // dp[1] = 9, (1, 2, 3, ..., 9)
    // dp[2] = 17, (10, 12, 21, 23, .., 87, 89, 98)
    // dp[3] = ?, (101, 121, 123, 210, 212, 232, 234, ..., 876, 878, 898, 987, 989)
    // dp[n] = dp[n - 1] * 2 로 깔끔하게 되지 않음..
    
    // dp[n][h] : 1의 자리수가 h 이며, 길이가 n 인 계단수 개수
    // dp[n][0] = dp[n - 1][1]
    // dp[n][1] = dp[n - 1][0] + dp[n - 1][2]
    // ... 1 ~ 8 까지는 비슷, dp[n][h] = dp[n - 1][h - 1] + dp[n - 1][h + 1]
    // dp[n][8] = dp[n - 1][9] + dp[n - 1][7]
    // dp[n][9] = dp[n - 1][8]
    
    int n = 0;
    cin >> n;
    
    vector<vector<long>> dp(n + 1, vector<long>(11, 0));
    long mod = 1000000000;
    
    // 초기화
    dp[1][0] = 0;
    for (int i = 1; i <= 9; i++) {
        dp[1][i] = 1;
    }
    
    // 점화
    for (int i = 2; i <= n; i++) {
        
        dp[i][0] = dp[i - 1][1];
        dp[i][9] = dp[i - 1][8];
        
        for (int j = 1; j <= 8; j++) {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % mod;
        }
    }
    
    long answer = 0;
    for (int i = 0; i <= 9; i++) {
        answer = (answer + dp[n][i]) % mod;
    }
    
    cout << answer;
    
    return 0;
}