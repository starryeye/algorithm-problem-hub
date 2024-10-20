#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 전체 층, 시작 층, 목표 층, 한번에 몇층을 위로 가는지, 한번에 몇층을 아래로 가는지
int bfs(int totalFloor, int start, int goal, int up, int down, vector<bool>& check) {
    
    queue<int> que;
    
	check[start] = true;
	que.push(start);

    int result = 0;
    
	while (!que.empty()) {
        
		int quesize = que.size();
		for (int a = 0; a < quesize; a++) {
            
			int cur = que.front();
			que.pop();

			if (cur == goal)
				return result;

			int next[2];
			next[0] = cur + up;
			next[1] = cur - down;

			for (int i = 0; i < 2; i++) {
				if (next[i] >= totalFloor || next[i] < 0 || check[next[i]] == true)
					continue;

				que.push(next[i]);
				check[next[i]] = true;
			}
		}
		result++;
	}
	return -1;
}

int main() {
    
    // 전체 층, 시작 층, 목표 층, 한번에 몇층을 위로 가는지, 한번에 몇층을 아래로 가는지
    int f, s, g, u, d;
	cin >> f >> s >> g >> u >> d;
    
    vector<bool> check(f);
    
    int ret = 0;
	ret = bfs(f, s - 1, g - 1, u, d, check); // 코드 상에선 -1

	if (ret == -1) {
		cout << "use the stairs";
	} else {
        cout << ret;
    }

	return 0;
}