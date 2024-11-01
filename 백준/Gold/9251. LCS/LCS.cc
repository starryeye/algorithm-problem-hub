#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
    LCS (Longest Common Subsequence) 최장 공통 부분 수열 문제
    dp[i][j] : str1 의 i index, str2 의 j index 까지 고려했을 때 LCS 길이
*/

int main() {
    
    string str1, str2;
    cin >> str1 >> str2;

    int len1 = str1.length();
    int len2 = str2.length();
    
    // DP 테이블 초기화: (len1 + 1) x (len2 + 1) 크기, 모두 0으로 초기화
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    // DP 테이블 채우기
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            
            if (str1[i - 1] == str2[j - 1]) { // 현재 문자가 동일하면, 이전 값에 +1을 더해 갱신
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else { // 현재 문자가 다르면, 위쪽 또는 왼쪽 값 중 큰 값 선택
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    // 최종 LCS 길이 출력: dp[len1][len2]가 두 문자열의 LCS 길이
    cout << dp[len1][len2] << endl;

    return 0;
}
