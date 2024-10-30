#include <iostream>

using namespace std;

static int n;
static long dp[1001];
static long mod = 10007;

int main() {
    
    cin >> n;
    
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
    }
    
    cout << dp[n];
    
    return 0;
}