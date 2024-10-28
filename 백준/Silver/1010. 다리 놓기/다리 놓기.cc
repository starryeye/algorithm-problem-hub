#include <iostream>

using namespace std;

static int T, N, M;
static int d[30][30]; // 0 < N <= M < 30

int main() {
    
    // 문제를 자세히 보면, M개 중 N개를 선택하는 조합 문제이다.
    
    for (int i = 0; i < 30; i++) {
        d[i][0] = 1;
        d[i][1] = i;
        d[i][i] = 1;
    }
    
    for (int i = 2; i < 30; i++) {
        for (int j = 1; j < i; j++) {
            d[i][j] = d[i - 1][j] + d[i - 1][j - 1];
        }
    }
    
    cin >> T;
    
    for (int i = 0; i < T; i++) {
        cin >> N >> M;
        cout << d[M][N] << '\n';
    }
    
    return 0;
}