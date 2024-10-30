#include <iostream>

using namespace std;

static int N, L, R;
static long mod = 1000000007;
static long dp[101][101][101];

int main() {
    
    cin >> N >> L >> R;
    
    // dp[n][l][r] : 빌딩 개수가 n개, 왼쪽에서 보면 l개가 보이고 오른쪽에서 보면 r개가 보일때 빌딩 배치 경우의 수
    // 가장 큰 빌딩 부터 배치한다고 생각하면 편하다.
    dp[1][1][1] = 1; // 빌딩이 1개이면, 빌딩 배치 경우의 수는 1개
    
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j <= L; j++) {
            for (int k = 1; k <= R; k++) {
                dp[i][j][k] = (
                    dp[i - 1][j][k] * (i - 2) // 가장 작은 빌딩을 가운데에 놓음
                    + dp[i - 1][j][k - 1] // 가장 작은 빌딩을 오른쪽에 놓음
                    + dp[i - 1][j - 1][k] // 가장 작은 빌딩을 왼쪽에 놓음
                ) % mod;
            }
        }
    }
    
    cout << dp[N][L][R];
}