#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    
    int n, m;
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));
    vector<vector<int>> dp(n, vector<int>(m, 0));
    int max_side = 0;  // 최대 정사각형의 변의 길이

    // 입력 받기
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            matrix[i][j] = c - '0';  // 문자 '0'과 '1'을 정수로 변환
        }
    }

    // DP 테이블 채우기
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 1) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;  // 첫 행이나 첫 열에서는 1 그대로 사용
                } else {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                }
                max_side = max(max_side, dp[i][j]);  // 최대 변의 길이 갱신
            }
        }
    }

    // 최대 정사각형의 넓이 출력
    cout << max_side * max_side << '\n';

    return 0;
}
