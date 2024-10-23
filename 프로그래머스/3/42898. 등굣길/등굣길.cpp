#include <string>
#include <vector>

using namespace std;

int solution(int m, int n, vector<vector<int>> puddles) {

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); // 0 으로 초기화

    dp[1][1] = 1;  // 시작점

    // 웅덩이 위치 표시
    for (auto &puddle : puddles)
        dp[puddle[1]][puddle[0]] = -1;  // 웅덩이는 -1로 표시

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            
            if (dp[i][j] == -1) { // 웅덩이는 경로 계산 제외
                dp[i][j] = 0;
                continue;
            }
            
            if (i > 1) 
                dp[i][j] += dp[i - 1][j] % 1000000007;  // 위쪽에서 오는 경로
            
            if (j > 1) 
                dp[i][j] += dp[i][j - 1] % 1000000007;  // 왼쪽에서 오는 경로
        }
    }

    return dp[n][m] % 1000000007;  // 정답을 1,000,000,007로 나눈 나머지 반환
}
