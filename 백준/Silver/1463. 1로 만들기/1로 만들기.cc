#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int n;
static vector<int> d; // d[i] : i 를 1 로 만드는 최소의 연산 횟수

int main() {
    
    cin >> n;
    
    d.resize(n + 1);
    
    // 초기화
    d[1] = 0;
    
    for (int i = 2; i <= n; i++) {
        
        d[i] = d[i - 1] + 1; // -1 연산 고려
        
        if (i % 2 == 0) {
            d[i] = min(d[i], d[i / 2] + 1); // /2 연산 고려 
        }
        
        if (i % 3 == 0) {
            d[i] = min(d[i], d[i / 3] + 1); // /3 연산 고려
        }
    }
    
    cout << d[n];
    
    return 0;
}