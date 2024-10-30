#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    // dp[i] : 수열 i index를 "포함하는" 연속 부분 수열 중 가장 합이 가장 큰 값
    // dp[i] = max(dp[i - 1] + array[i], array[i])
    // 최종 답 : dp의 모든 원소 중 가장 큰 값이 답..
    
    // 하지만, 문제는 하나의 원소를 빼도 된다..
    // dp[i][j] : j index를 제거함. (0 은 제거하지 않음)
    // -> 이렇게도 한번 풀어보기..
    // 
    // 여기서는 왼쪽에서 오른쪽으로 dp[i] 를 풀고 오른쪽에서 왼쪽으로 dp[i] 를 풀어서
    // dpL[n - 1] + dpR[n + 1] 의 최댓 값을 구하는 방식으로 풀겠다..
    
    int n = 0;
    cin >> n;
    
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int answer = arr[0]; // INT_MIN 으로 하면 틀린 답임
    
    // 왼쪽에서 오른쪽 점화
    vector<int> dpL(n, 0);
    dpL[0] = arr[0];
    for (int i = 1; i < n; i++) {
        dpL[i] = max(dpL[i - 1] + arr[i], arr[i]);
        answer = max(answer, dpL[i]); // 기본 값은 원소 제거하지 않은 경우로 한다.
    }
    
    // 오른쪽에서 왼쪽 점화
    vector<int> dpR(n, 0);
    dpR[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        dpR[i] = max(dpR[i + 1] + arr[i], arr[i]);
    }
    
    // 한개의 원소 빼보기
    // 양끝 원소를 빼보는것은 두개의 점화 계산때 자동으로 고려됨
    for (int i = 1; i < n - 1; i++) {
        answer = max(answer, dpL[i - 1] + dpR[i + 1]);
    }
    
    cout << answer << '\n';
    
    return 0;
}