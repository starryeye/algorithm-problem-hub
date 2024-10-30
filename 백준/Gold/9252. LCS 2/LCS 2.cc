#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

static int n;
static int dp[1001][1001];
static string a, b;
static vector<char> path;

void getLCSText(int y, int x) {
    
    if (y == 0 || x == 0) {
        return;
    }
    
    if (a[y - 1] == b[x - 1]) { // 문자가 동일하면 LCS 에 기록하고 왼쪽 대각선으로 이동
        path.push_back(a[y - 1]);
        getLCSText(y - 1, x - 1);
    } else {
        
        if (dp[y][x - 1] > dp[y - 1][x]) {// 왼쪽 위쪽 비교하여 더 큰쪽으로 이동
            getLCSText(y, x - 1);
        } else {
            getLCSText(y - 1, x);
        }
    }
}

int main() {
    
    cin >> a >> b;
    
    int n = a.size();
    int m = b.size();
    
    if (n == 0 || m == 0) {
        cout << "0";
        return 0;
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    // LCS 길이 출력
    cout << dp[n][m] << '\n';
    
    // LCS 경로 추적
    getLCSText(n, m);
    
    // 경로 역순 출력
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i];
    }
    cout << '\n';
    
    return 0;
}
