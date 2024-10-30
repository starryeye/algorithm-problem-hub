#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

// 발을 이동할 때 드는 힘, mp[1][2] : 1에서 2로 이동할 때 드는 힘
static int mp[5][5] = { // 0 ~ 4 -> 0 ~ 4
    {0, 2, 2, 2, 2},
    {2, 1, 3, 4, 3},
    {2, 3, 1, 3, 4},
    {2, 4, 3, 1, 3},
    {2, 3, 4, 3, 1}
};

int main() {
    
    // dp[n][l][r] : n개 수열을 수행, 왼쪽 발이 l 오른쪽 발이 r 자리에 있을 때 최소 누적 힘
    vector<vector<vector<long>>> dp(100001, vector<vector<long>>(5, vector<long>(5, 400004))); // 충분히 큰값으로 초기화
    dp[0][0][0] = 0;
    
    int s = 0;
    
    while (true) {
        
        int n = 0; // 입력 수열 원소 (이동 위치)
        cin >> n;
        
        if (n == 0) { // 입력 마지막, 종료
            break;
        }
        
        s++; // 이동 횟수 (수열에서 몇번째 원소까지 진행했는지)
        
        // 오른쪽 발을 이동해 현재 발 위치로 만들 수 있는 경우의 수
        for (int l = 0; l <= 4; l++) { // 왼쪽 발 모습
            
            if(n == l) { // 두 발이 같은 자리면 스킵
                continue;
            }
            
            for (int r = 0; r <= 4; r++) {
                // 오른쪽 발을 r -> n 이동
                // 오른쪽 발을 옮겨서 현재 모습이 되었을 때 최소 힘 저장
                dp[s][l][n] = min(
                    dp[s - 1][l][r] + mp[r][n],
                    dp[s][l][n]
                );
            }
        }
        
        // 왼쪽 발을 이동해 현재 발 위치로 만들 수 있는 경우의 수
        for (int r = 0; r <= 4; r++) { // 오른쪽 발 모습
            
            if(n == r) { // 두 발이 같은 자리면 스킵
                continue;
            }
            
            for (int l = 0; l <= 4; l++) {
                // 왼쪽 발을 l -> n 이동
                // 왼쪽 발을 옮겨서 현재 모습이 되었을 때 최소 힘 저장
                dp[s][n][r] = min(
                    dp[s - 1][l][r] + mp[l][n],
                    dp[s][n][r]
                );
            }
        }
    }
    
    long answer = INT_MAX;
    
    for (int i = 0; i <= 4; i++) {
        for (int j = 0; j <= 4; j++) {
            answer = min(answer, dp[s][i][j]); // 최솟값
        }
    }
    
    cout << answer;
    
    return 0;
}