#include <iostream>

using namespace std;

static int T, K, N;
static int D[15][15]; // first : 층, second : 호, value : 몇명이 사는지

int main() {
    
    // 초기화
    for (int i = 0; i < 15; i++) {
        D[i][1] = 1; // i층 1호 에는 항상 1명
        D[0][i] = i; // 0층 i호 에는 항상 i명
    }
    
    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 15; j++) {
            
            // 1. 문제를 읽고 아래와 같이 식을 만들어본다.
            //         D[a][b] = D[a - 1][0] + ... + D[a - 1][b - 1] + D[a - 1][b]
            // 2. D[a][b] 는 D[a][b - 1] 에 D[a - 1][b] 를 더하면 된다는 사실을 알아차려야한다.
            //         = (D[a - 1][0] + ... + D[a - 1][b - 1]) + D[a - 1][b]
            //         = D[a][b - 1] + D[a - 1][b]
            // 3. 따라서 아래의 일반 점화식이 도출된다.
            D[i][j] = D[i][j - 1] + D[i - 1][j];
        }
    }
    
    cin >> T;
    
    for (int i = 0; i < T; i++) {
        cin >> K >> N;
        cout << D[K][N] << '\n';
    }
    
    return 0;
}