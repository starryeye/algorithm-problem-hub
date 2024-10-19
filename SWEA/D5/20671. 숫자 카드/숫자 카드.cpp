#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
  
using namespace std;
 
long long mod = 1000000007;
bool customCompare(const pair<string, int>& a, const pair<string, int>& b) {
    return a.first + b.first < b.first + a.first;
}
 
long long stringToModInt(const string &s) {
    long long ret = 0;
    for (char digit : s) {
        ret = (ret * 10 + (digit - '0')) % mod;
    }
    return ret;
}
 
int main() {
    vector<long long> tenof(35);
    tenof[0] = 1;
    for(int i = 1;i < 35;i++) tenof[i] = (tenof[i-1] * 10) % mod;
    int T; cin >> T;
    for(int t = 1;t <= T;t++) {
        int N; cin >> N;
        vector<pair<string,int>> arr;
        arr.reserve(2*N);
        for(int i = 0;i < N;i++) {
            string a,b;
            cin >> a >> b;
            arr.push_back({a,i});
            arr.push_back({b,i});
        }
        sort(arr.begin(),arr.end(),customCompare);
        int _N = 2 * N;
        long long answer = 0;
        vector<long long> possib(N,2);
        for(int i = _N-1;i >= 0;i--) {
            long long cur = 1;
            for(int j = 0;j < N;j++) {
                //자신 제외
                if(j != arr[i].second) {
                    cur = (cur * possib[j]) %mod;
                }
            }
            //answer에 누적
            answer = (answer + (stringToModInt(arr[i].first) * cur)%mod)%mod;
            //possib 업데이트 with arr[i]
            int target = arr[i].second;
            int toadd = arr[i].first.size();
            possib[target] = (possib[target] + tenof[toadd] - 1) % mod;
        }
        cout << '#' << t << " " << answer << endl;
    }
    return 0;
}