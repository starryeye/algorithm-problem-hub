// 기본 지식 : (N * M) * (M * K) 를 연산하면 (N * K) 가 나온다.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

static int N;
static vector<pair<int, int>> M; // 행렬사이즈, fisrt/second
static long dp[502][502]; // dp[i][j] : i ~ j 구간의 행렬을 합치는데 드는 최소 연산 횟수

int execute(int s, int e) {
    
    int result = INT_MAX;
    
    if (dp[s][e] != -1) { // 메모이제이션
        return dp[s][e];
    }
    
    if (s == e) { // 행렬 1개이면 연산횟수 0
        return 0;
    }
    
    if (s + 1 == e) { // 인접 행렬이면 직접 계산
        return M[s].first * M[s].second * M[e].second;
    }
    
    // 행렬이 3개 이상이다.
    for (int i = s; i < e; i++) {
        
        // 행렬의 개수가 N개이고
        // N 번째 행렬을 제외한 0 ~ N-1 구간의 모든 부분 구역에 대해 dp 값을 알고 있다면..
        // dp[1][N] 을 어떻게 구할 수 있을까..
        // dp[1][N-1] + dp[N][N] + 두 구간을 합하는데 드는 연산횟수
        // dp[1][N-2] + dp[N-1][N] + 두 구간을 합하는데 드는 연산횟수
        // ...
        // dp[1][1] + dp[2][N] + 두 구간을 합하는데 드는 연산횟수
        // 위의 값들 중 최솟값을 dp[1][N] 으로 정하면 된다.
        result = min(
            result,
            execute(s, i) + execute(i + 1, e) + M[s].first * M[i].second * M[e].second
        );
    }
    dp[s][e] = result;
    
    return result;
}

int main() {
    
    cin >> N;
    M.resize(N + 1);
    
    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < N + 1; j++) {
            dp[i][j] = -1;
        }
    }
    
    for (int i = 1; i <= N; i++) {
        int y, x;
        cin >> y >> x;
        M[i] = {y, x};
    }
    
    cout << execute(1, N);
    
    return 0;
}