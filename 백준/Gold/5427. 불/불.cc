#include <iostream>
#include <queue>

using namespace std;

int map[1001][1001];
string str[1001];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int w, h;

struct Position
{
	int y, x, tick;
};

queue<Position> manque;
queue<Position> flame;

int mancheck[1001][1001];

int bfs()
{
    // 사람이 더이상 이동 불가능할때 까지 진행
	while (!manque.empty()) {
        
		// 불 이동.
		int flamesize = flame.size(); //한 틱기준의 큐 개수만큼 움직임
		for (int i = 0; i < flamesize; i++) {
            
			Position fire = flame.front();
			flame.pop();
			
            for (int j = 0; j < 4; j++) {
				int y = fire.y + dy[j];
				int x = fire.x + dx[j];

				if (y < 0 || x < 0 || y >= h || x >= w)
					continue;
				if (map[y][x] == 1 || map[y][x] == 2)
					continue;

				map[y][x] = 2;
				flame.push({ y, x, fire.tick + 1 });
			}
		}

        // 사람 이동
		int pathsize = manque.size(); //한 틱기준의 큐 개수만큼 움직임
		for (int i = 0; i < pathsize; i++) {
            
			Position node = manque.front();
			manque.pop();

			//탈출
			if (node.y == 0 || node.x == 0 || node.y == h - 1 || node.x == w - 1) {
				return node.tick + 1;
			}

			for (int j = 0; j < 4; j++) {
                
				int nextY = node.y + dy[j];
				int nextX = node.x + dx[j];
				int nextTick = node.tick + 1;

				if (nextY < 0 || nextX < 0 || nextY >= h || nextX >= w)
					continue;
				if (mancheck[nextY][nextX] == true || map[nextY][nextX] == 1 || map[nextY][nextX] == 2)
					continue;

				manque.push({ nextY, nextX, nextTick });
				mancheck[nextY][nextX] = true;
			}
		}
		
	}

	return -1;
}

void solve()
{
	//실행
	int ret = bfs();
	if (ret < 0) {
		cout << "IMPOSSIBLE" << endl;
	} else {
		cout << ret << endl;
	}


	//초기화
	while (!manque.empty())
		manque.pop();
	while (!flame.empty())
		flame.pop();

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			map[i][j] = 0;
			mancheck[i][j] = 0;
		}
	}
	
}


int main() {
    
	int tc;
	cin >> tc;

	while (tc--) {
        
		cin >> w >> h;

		for (int i = 0; i < h; i++) {
			
            cin >> str[i];
            
			for (int j = 0; j < w; j++) {
				
                if (str[i][j] == '#') //벽
					map[i][j] = 1;
				else if (str[i][j] == '.') //빈칸
					map[i][j] = 0;
				else if (str[i][j] == '*') { //불
					map[i][j] = 2;
					flame.push({ i, j, 0 });
				} else { //사람
					manque.push({ i, j, 0 });
					mancheck[i][j] = true;
				}

			}
		}

		solve();
	}

	return 0;
}