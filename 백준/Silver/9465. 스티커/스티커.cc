#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // memset
using namespace std;

int arr[2][100001];
int dp[2][100001];

int main() {
    
	int t = 0;
	cin >> t;

	for (int i = 0; i < t; i++) {
        
		int n;
		cin >> n;

		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < n; k++) {
                
                int s;
				cin >> s;
				arr[j][k] = s;
			}
		}

		
		dp[0][0] = arr[0][0];
		dp[1][0] = arr[1][0];

		if (n >= 2) {
            
			dp[0][1] = dp[1][0] + arr[0][1];
			dp[1][1] = dp[0][0] + arr[1][1];

			if (n >= 3) {
                
				for (int k = 2; k < n; k++) {
					dp[0][k] += max(dp[1][k - 2], dp[1][k - 1]) + arr[0][k];
					dp[1][k] += max(dp[0][k - 2], dp[0][k - 1]) + arr[1][k];
				}
			}
		}


		cout << max(dp[0][n - 1], dp[1][n - 1]) << '\n';
		memset(arr, 0, sizeof(arr));
		memset(dp, 0, sizeof(dp));
	}
	return 0;
}