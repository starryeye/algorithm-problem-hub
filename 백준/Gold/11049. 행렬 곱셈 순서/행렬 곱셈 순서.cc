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

/*
// 위는 탑다운, 아래는 바텀업
#include <iostream>
#include <vector>
#include <climits>  // INT_MAX를 사용하기 위해 포함

using namespace std;


// 최소 행렬 곱셈 연산 수를 계산하는 DP 문제
// dp[i][j] : i번째 행렬부터 j번째 행렬까지 곱할 때 필요한 최소 연산 횟수

int main() {
    int N;  // 행렬의 개수
    cin >> N;

    // 행렬의 크기 입력 받기
    vector<int> rows(N + 1), cols(N + 1);  // 행렬 크기를 1부터 N까지 사용하기 위해 N+1 크기 배열
    for (int i = 1; i <= N; i++) {
        cin >> rows[i] >> cols[i];  // i번째 행렬의 크기 rows[i] x cols[i]
    }

    // DP 테이블 초기화 (N+1 x N+1 크기, 큰 값으로 초기화)
    vector<vector<int>> dp(N + 1, vector<int>(N + 1, INT_MAX));

    // 자기 자신 곱셈의 경우 연산이 필요 없으므로 0으로 초기화
    for (int i = 1; i <= N; i++) {
        dp[i][i] = 0;
    }

    // 행렬 곱셈 구간 길이 l을 1부터 N-1까지 순차적으로 늘려가며 dp 계산
    for (int l = 1; l < N; l++) {           // l은 구간 길이 (1 ~ N 의 구간길이는 N-1 이다.)
        for (int i = 1; i + l <= N; i++) {   // i는 구간의 시작 인덱스
            int j = i + l;                   // j는 구간의 끝 인덱스 (i부터 l만큼 떨어진 위치)

            // i번째부터 j번째 행렬을 곱하는 최소 연산 수 찾기
            for (int k = i; k < j; k++) {    
                // dp[i][k]: i~k까지의 최소 연산 횟수
                // dp[k+1][j]: k+1~j까지의 최소 연산 횟수
                // rows[i] * cols[k] * cols[j]: 두 행렬을 곱할 때 발생하는 연산 횟수
                int cost = dp[i][k] + dp[k + 1][j] + rows[i] * cols[k] * cols[j];
                dp[i][j] = min(dp[i][j], cost);  // 최소값을 갱신
            }
        }
    }

    // 결과 출력: 1번부터 N번까지 모든 행렬을 곱할 때 필요한 최소 연산 수
    cout << dp[1][N] << endl;

    return 0;
}
*/
