#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

int dfs(int cur, int p, int count, unordered_map<int, int>& m) {
    
	count++;
	m[cur] = count; // cur 은 count 번째 노드이다.

	//int next = pow((node / 1000) % 10, p) + pow((node / 100) % 10, p) + pow((node / 10) % 10, p) + pow(node % 10, p);

	int next = 0;
	while (cur) {
		next += (int)pow((cur % 10), p);
		cur /= 10;
	}

	if (m.find(next) == m.end()) {
		return dfs(next, p, count, m);
	} else {
		return m[next] - 1;
	}
}


int main() {
    
	int a, p;
    unordered_map<int, int> m;

	cin >> a >> p;

	int ret = dfs(a, p, 0, m);

	cout << ret;

	return 0;
}