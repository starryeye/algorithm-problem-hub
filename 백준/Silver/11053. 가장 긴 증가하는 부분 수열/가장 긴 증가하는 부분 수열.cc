#include <iostream>
#include <algorithm>

using namespace std;
int arr[1001];  // 원본 수열을 저장하는 배열
int dp[1001];   // LIS 길이를 저장하는 DP 테이블

// LIS (최장 증가 부분 수열)은 주어진 수열에서 증가하는 부분 수열 중 가장 긴 것을 찾는 문제
// 부분 수열이란 원래 배열의 순서를 그대로 유지한 채 일부 요소만 선택한 수열을 의미
// ex, [10, 20, 10, 30, 20, 50]일 때, LIS는 [10, 20, 30, 50]로 길이가 4 이다.

// dp[i] : i번째 요소를 마지막으로 하는 LIS의 길이 (i번째 요소를 포함한다는 의미)

// 참고..
// 그리디 문제가 아닌 이유..
// 4, 5, 6, 1, 2, 3, 4, 10, 11
// 그리디의 경우 : 4, 5, 6 10, 11
// dp로 풀 경우 : 1, 2, 3, 4, 10, 11

int main() {
	
	int n = 0;
	cin >> n;

	// 수열 입력
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	
	// LIS 계산: 각 원소를 마지막으로 하는 LIS 길이 계산
	for (int current = 1; current <= n; current++) {
        
        dp[current] = 1;  // 최소 길이는 자기 자신만 포함하는 길이 1
        
		for (int previous = 1; previous < current; previous++) {  // 현재 위치 이전의 요소들을 탐색

			// 증가 수열 조건 확인: arr[previous] < arr[current]
			// 이전 위치 `previous`에서 얻을 수 있는 최대 LIS 길이를 선택하여 갱신
			if (arr[previous] < arr[current]) {
				dp[current] = max(dp[current], dp[previous] + 1);  // 더 긴 LIS로 갱신
			}
		}
	}
    
    int answer = 0;
    
    // dp 테이블에서 가장 큰 값이 최장 증가 부분 수열의 길이
	for (int i = 1; i <= n; i++) {
		answer = max(answer, dp[i]);
	}

	cout << answer << endl;  // 최장 증가 부분 수열의 길이를 출력

	return 0;
}
