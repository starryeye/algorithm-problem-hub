#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int result;
int map[8][8];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void bfs() {
    
	queue<pair<int, int>> que; // y,x

    // 오염 스타팅 좌표 찾기
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
            
			if (map[i][j] == 2) {
				que.push(make_pair(i, j));
			}
		}
	}

    // 오염 퍼뜨리기
	while (!que.empty()) {
        
		int y = que.front().first;
		int x = que.front().second;
		que.pop();

		for (int ii = 0; ii < 4; ii++) {
            
			int nextY = y + dy[ii];
			int nextX = x + dx[ii];

            if (nextY < 0 || nextX < 0 || nextY >= n || nextX >= m) {
                continue;
            }
            
            if (map[nextY][nextX] != 0) {
                continue;
            }

			map[nextY][nextX] = 3; //오염
			que.push(make_pair(nextY, nextX));
		}
	}

	int sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			
            if (map[i][j] == 0) { // 안전구역 갯수
				sum++;
			}
			else if (map[i][j] == 3) {
				map[i][j] = 0; //원복시키기
			}
		}
	}

	result = max(result, sum);
}

void wall(int count) {
    
	if (count == 3) {
		bfs();
		return;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			
            if (map[i][j] == 0) {
				map[i][j] = 1; // 벽 세우기
				wall(count + 1);
				map[i][j] = 0; // 벽 원복
			}
		}
	}

}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	wall(0);

	cout << result;

	return 0;
}