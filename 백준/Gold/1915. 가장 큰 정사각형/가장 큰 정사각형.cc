#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // 입력 행렬과 DP 테이블 초기화
    vector<vector<int>> matrix(n, vector<int>(m));
    vector<vector<int>> dp(n, vector<int>(m, 0));
    int max_side = 0;  // 가장 큰 정사각형의 변 길이

    // 입력 처리 (문자 '0'과 '1'을 정수로 변환)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            matrix[i][j] = c - '0';  // '0' 또는 '1'을 정수로 저장
        }
    }

    // DP 테이블 채우기
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 1) {  // 현재 위치가 1인 경우에만 정사각형 확장 가능
                if (i == 0 || j == 0) {
                    // 첫 행 또는 첫 열은 정사각형을 확장할 수 없으므로 그대로 사용
                    dp[i][j] = 1;
                } else {
                    // 점화식: 현재 위치에서 끝나는 정사각형의 변 길이 계산
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    /*
                      dp[i-1][j]   : 위쪽 값 (i, j)의 바로 위에 있는 위치
                      dp[i][j-1]   : 왼쪽 값 (i, j)의 바로 왼쪽에 있는 위치
                      dp[i-1][j-1] : 대각선 위쪽 값 (i, j)의 대각선 왼쪽 위에 있는 위치
                      
                      -> 세 위치의 최소값에 +1을 더함.
                      -> 세 위치 중 하나라도 정사각형을 만들지 못하면 현재 위치도 확장 불가.
                    */
                }
                // 최대 변의 길이 갱신
                max_side = max(max_side, dp[i][j]);
            }
        }
    }

    // 최종 넓이 출력 (가장 큰 정사각형의 변 길이 제곱)
    cout << max_side * max_side << '\n';

    return 0;
}
