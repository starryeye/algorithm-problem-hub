#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    // 조합 문제..
    // 총 N 개 중 K 개를 선택하는 경우의 수(순서 X) 이다.
    
    int n = 0;
    int k = 0;
    cin >> n >> k;
    
    // d[i][j]
    // i : 총 i 개 (or 0 index 부터 i index 까지의 item 을 고려한다는 의미를 부여할 수 도 있다. 이때는 총 i + 1개)
    // j : j 개를 선택
    
    // d[n][n] 을 접근하기 위해 +1 해준다.
    vector<vector<int>> d(n + 1, vector<int>(n + 1, 0));
    
    // d 초기화
    for (int i = 0; i <= n; i++) {
        d[i][1] = i; // 총 i개 중, 1개를 선택할 경우의 수는 i가지이다.
        d[i][0] = 1; // 총 i개 중, 0개를 선택할 경우의 수는 1가지이다.
        d[i][i] = 1; // 총 i개 중, i개를 선택할 경우의 수는 1가지이다.
    }
    
    for (int i = 2; i <= n; i++) { // 총 개수
        for (int j = 1; j < i; j++) { // 선택 수, 총 개수 i 보다 선택 수 j 가 클 수 없음.
            
            // d[i][j] : 총 i 개 중, j 개를 순서 없이 선택하는 모든 경우의 수 는...
            // d[i - 1][j] : 총 i-1 개 중, j 개를 선택하는 모든 경우의 수(i 번째 item 선택 X)와..
            // d[i - 1][j - 1] : 총 i-1 개 중, j-1 개를 선택하는 모든 경우의 수(i 번째 item 선택 O)를 더한 값이다.
            d[i][j] = d[i - 1][j] + d[i - 1][j - 1];
        }
    }
    
    cout << d[n][k];
    
    return 0;
}