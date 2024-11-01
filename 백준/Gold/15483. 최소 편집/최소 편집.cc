#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
    최소 편집 거리
    dp[i][j] : A의 1 ~ i 번째 원소들과 B의 1 ~ j 번째 원소들을 같게 만드는데 필요한 최소 편집 거리를 의미
    index 가 아닌 "번째"로 의미를 두고, 0번째의 경우 빈문자열이다.
*/

int main() {
    
    string A, B;
    cin >> A >> B;  // 두 문자열 입력 받기

    int lenA = A.size();
    int lenB = B.size();
    
    // DP 테이블 생성: (lenA + 1) x (lenB + 1) 크기, 모두 0으로 초기화
    // index 가 아닌 "번째"로 의미를 두고, 0번째의 경우 빈문자열이다.
    vector<vector<int>> dp(lenA + 1, vector<int>(lenB + 1, 0));
    
    // 초기화, 한문자열이 빈문자열일 경우라고 생각하면 편하다.
    for (int i = 0; i <= lenA; i++) {
        // dp[i][0] : A에서 1 ~ i 번째 문자를 모두 삭제하여, 빈 문자열로 만드는 데 필요한 최소 연산 횟수
        dp[i][0] = i;
    }
    for (int j = 0; j <= lenB; j++) {
        dp[0][j] = j;
    }
    
    // DP 테이블 채우기
    for (int i = 1; i <= lenA; i++) {
        for (int j = 1; j <= lenB; j++) {
            
            if (A[i - 1] == B[j - 1]) {
                // A의 i번째 원소와 B의 j번째 원소가 같다면, 이전 상태의 편집 거리를 그대로 가져옴 (편집 안함)
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // A의 i번째 원소와 B의 j번째 원소가 다르면, 세 가지 편집 연산 중 최소 비용 선택
                dp[i][j] = min({ //
                    dp[i - 1][j] + 1,     // 삭제: A의 i번째 문자 삭제 (dp[4][3] 이라면, dp[3][3] 에서 연산하나 필요하다. 라고 받아드리자) 
                    dp[i][j - 1] + 1,     // 삽입: A에 B의 j번째 문자 삽입 (dp[2][3] 이라면, dp[3][3] 에서 연산하나 필요하다. 라고 받아드리자) 
                    dp[i - 1][j - 1] + 1  // 교체: A의 i번째 문자를 B의 j번째 문자로 교체
                });
            }
        }
    }
    
    // 최종 편집 거리 출력
    cout << dp[lenA][lenB] << endl;

    return 0;
}
