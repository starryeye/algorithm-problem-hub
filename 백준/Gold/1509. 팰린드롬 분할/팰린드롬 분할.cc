#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
    최소 팰린드롬 분할
    dp[i]: 문자열의 0 ~ i index까지 고려했을때..
        부분 문자열을 최소 개수의 팰린드롬으로 분할하는 데 필요한 최소 분할 횟수(부분 문자열 개수)
    isPalindrome[start][end]: 문자열의 start ~ end 구간이 팰린드롬인지 여부를 저장하는 배열
    
    참고. 
    분할 횟수 = 팰린드롬인 부분 문자열 개수이다.
    그래서, 분할을 하지않아도 전체 문자열이 그자체로 부분 문자열이므로 1이 정답
    분할 한번 해서 부분 문자열 2개가 나오면 답은 2이다.
*/

int main() {
    
    string s;
    cin >> s;  // 문자열 입력 받기
    
    int n = s.size();
    
    // 팰린드롬 여부를 저장하는 배열 초기화
    vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
    
    // 팰린드롬 여부를 미리 계산
    for (int end = 0; end < n; end++) {
        for (int start = 0; start <= end; start++) {
            
            // start와 end가 같은 경우는 항상 팰린드롬
            if (start == end) {
                isPalindrome[start][end] = true;
            }
            // 인접한 두 문자가 같으면 팰린드롬
            else if (end - start == 1 && s[start] == s[end]) {
                isPalindrome[start][end] = true;
            }
            // start와 end가 다른 경우: 양 끝이 같고 내부 문자열이 팰린드롬이면 팰린드롬
            else if (s[start] == s[end] && isPalindrome[start + 1][end - 1]) {
                isPalindrome[start][end] = true;
            }
        }
    }

    // 최소 분할 횟수를 저장하는 dp 배열 초기화
    vector<int> dp(n, 0);

    // dp 배열 채우기
    for (int i = 0; i < n; i++) {
        // 초기값: 0 ~ i 전체가 팰린드롬인 경우, 분할 필요 없음
        if (isPalindrome[0][i]) {
            dp[i] = 1; // 그자체로 부분문자열
        } else {
            
            dp[i] = i + 1; // 최소 분할 횟수를 구하기 위해 초기 큰 값으로 설정
            
            // j를 기준으로 0 ~ j까지의 최소 분할 수에 +1을 하여 최소값을 갱신
            for (int j = 0; j < i; j++) {
                if (isPalindrome[j + 1][i]) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
    }

    // 최소 분할 횟수 출력 (dp[n-1]에 저장됨)
    cout << dp[n - 1] << endl;

    return 0;
}
