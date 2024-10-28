#include <iostream>
#include <vector>

using namespace std;

int main() {
    
    
    int n = 0;
    int k = 0;
    cin >> n >> k;
    
    // 이항 계수 1 문제와 동일 + 모듈러 연산
    // (A + B) mod N = (A mod N + B mod N) mod N
    
    // d[i][j] : 총 i개 중, j개를 선택하는 모든 경우의 수 (조합)
    vector<vector<int>> d(n + 1, vector<int>(n + 1, 0));
    
    // 초기화
    for (int i = 0; i <= n; i++) {
        d[i][0] = 1;
        d[i][1] = i;
        d[i][i] = 1;
    }
    
    // 점화
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            
            d[i][j] = d[i - 1][j] + d[i - 1][j - 1];
            d[i][j] = d[i][j] % 10007; // 모든 결과에 모듈러 연산 수행
        }
    }
    
    cout << d[n][k];
    
    return 0;
}