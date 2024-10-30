#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    // dp[n] : n 자리 이친수의 개수
    // dp[0] : 0
    // dp[1] : 1, (1)
    // dp[2] : 1, (10)
    // dp[3] : 2, (100, 101)
    // dp[4] : 3, (1000, 1010, 1001)
    // dp[5] : 5, (10000, 10100, 10010, 10101, 10001)
    // -> 규칙을 보아하니.. 일차원 배열로는 힘들듯..
    
    // dp[i][0], dp[i][1]..
    // dp[i][0] + dp[i][1] = i 자리 이친수의 개수
    // dp[i][0] : i 자리 이친수, 뒷자리(일의 자리수)가 0인 개수
    //         dp[i][0] = dp[i - 1][0] + dp[i - 1][1]
    // dp[i][1] : i 자리 이친수, 뒷자리(일의 자리수)가 1인 개수
    //         dp[i][1] = dp[i - 1][0]
    
    int n = 0;
    cin >> n;
    
    vector<vector<long>> dp(n + 1, vector<long>(2, 0));
    
    dp[1][0] = 0;
    dp[1][1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
        dp[i][1] = dp[i - 1][0];
    }
    
    cout << dp[n][0] + dp[n][1];
    
    return 0;
}