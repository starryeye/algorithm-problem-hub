#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int n;

static vector<int> t; // 상담을 완료하는 데 걸리는 기간
static vector<int> p; // 상담했을 때 받을 수 있는 금액

static vector<int> dp;

int main() {
    
    cin >> n;
    
    t.resize(n + 1);
    p.resize(n + 1);
    
    dp.resize(n + 2); // dp[n + 1] 때문임
    
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> p[i];
    }
    
    // dp[i] : i일 까지 상담을 했을 때, 받을 수 있는 최대 금액 (1일차 부터 i일까지 순서로 계산)
    // -> d[i] = max(d[t[x] + x] + p[x], d[i - 1])
    // i = t[x] + x... 
    // x 에 대하여 i 로 표현이 어려움..
    
    // dp[i]의 의미를 변경해야 편할듯..
    // dp[i] : i일 부터 퇴사일 까지 일을 했을 때, 받을 수 있는 최대 금액 (퇴사일 부터 역순으로 계산)
    // -> dp[i] = max(d[t[i] + i] + p[i], d[i + 1])
    // -> d[t[i] + i] + p[i] : i일 부터 시작하는 상담을 수행하겠다.
    //        (t[i] + i)일 부터 퇴사일 까지 일했을 때 받을 수있는 최대 금액에 i일 상담 더함
    // -> d[i + 1] : i일 부터 시작하는 상담을 수행하지 않겠다.
    
    for (int i = n; i >= 1; i--) {
        
        if (t[i] + i > n + 1) { // i일에 시작하는 상담을 퇴사일까지 끝낼수 없음 (퇴사일에 상담 가능하다.)
            dp[i] = dp[i + 1];
            continue; 
        }
        
        dp[i] = max(dp[t[i] + i] + p[i], dp[i + 1]);
    }
    
    cout << dp[1] << endl;
    
    return 0;
}

/*
// 브루트포스
#include <iostream>
using namespace std;
const int inf = -100000000;
int t[21];
int p[21];
int n;
int ans = 0;
void go(int day, int sum) {
    if (day == n+1) {
        if (ans < sum) ans = sum;
        return;
    }
    if (day > n+1) {
        return;
    }
    go(day+1, sum);
    go(day+t[day], sum+p[day]);
}
int main() {
    cin >> n;
    for (int i=1; i<=n; i++) {
        cin >> t[i] >> p[i];
    }
    go(1, 0);
    cout << ans << '\n';
    return 0;
}
*/