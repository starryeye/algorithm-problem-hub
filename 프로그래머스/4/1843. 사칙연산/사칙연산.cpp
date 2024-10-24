#include <vector>
#include <string>
#include <climits>
using namespace std;

/* 추후 이해 필요.. */
int solution(vector<string> arr) {
    
    int n = (arr.size() + 1) / 2; // 배열에서 숫자 갯수
    
    // dp[l][r][0] : 배열 l 에서 r 까지의 가능한 최솟값
    // dp[l][r][1] : 배열 l 에서 r 까지의 가능한 최댓값
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
    
    // 단일 숫자에 대한 초기화
    for (int i = 0; i < n; i++) {
        dp[i][i][0] = stoi(arr[i * 2]);
        dp[i][i][1] = stoi(arr[i * 2]);
    }
    
    for (int len = 2; len <= n; ++len) { // 부분 배열 길이
        
        // i : 부분 배열의 시작 인덱스
        // j : 부분 배열의 끝 인덱스
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            
            dp[i][j][0] = INT_MAX;
            dp[i][j][1] = INT_MIN;
            
            // k : i 인덱스 부터 j 인덱스 중간 어떤 인덱스
            for (int k = i; k < j; ++k) {
                
                int leftMin = dp[i][k][0]; // i부터 k까지의 부분 배열에서 계산된 최솟값
                int leftMax = dp[i][k][1]; // i부터 k까지의 부분 배열에서 계산된 최댓값
                
                int rightMin = dp[k + 1][j][0]; // k+1부터 j까지의 부분 배열에서 계산된 최솟값
                int rightMax = dp[k + 1][j][1]; // k+1부터 j까지의 부분 배열에서 계산된 최댓값
                
                char op = arr[2 * k + 1][0]; // 어떤 연산자인지 get

                if (op == '+') {
                    dp[i][j][0] = min(dp[i][j][0], leftMin + rightMin); // 최솟값 후보
                    dp[i][j][1] = max(dp[i][j][1], leftMax + rightMax); // 최댓값 후보
                } else {  // op : -
                    dp[i][j][0] = min(dp[i][j][0], leftMin - rightMax); // 최솟값 후보, - 이므로 max 를 이용
                    dp[i][j][1] = max(dp[i][j][1], leftMax - rightMin); // 최댓값 후보, - 이므로 min 을 이용
                }
            }
        }
    }
    
    return dp[0][n - 1][1]; // 0 에서 n-1 까지의 가능한 최댓값
}