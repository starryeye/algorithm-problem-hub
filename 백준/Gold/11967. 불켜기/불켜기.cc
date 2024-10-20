#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct pos {
	int y, x;
};

vector<pos> map[101][101]; //스위치

int light[101][101]; //불


int dy[4] = { -1, 1, 0, 0 };
int dx[4] = {0, 0, -1, 1};

int lightcount;// 불을 켠 방


void bfs(pos start) {
    
	queue<pos> que;
	bool check[101][101] = {false,};

	if (light[start.y][start.x] == 0) { //스타팅포인트 불키고 count +1
		lightcount++;
		light[start.y][start.x] += 1;
	}

	check[start.y][start.x] = true;
	que.push(start);
    
	int switchCount = map[start.y][start.x].size();
	for (int i = 0; i < switchCount; i++) {
		pos temp = map[start.y][start.x][i];

		if (light[temp.y][temp.x] == 0) {
			lightcount++;
			light[temp.y][temp.x] += 1; //불킨다.
		}
	}

	while (!que.empty()) {
		pos cur = que.front();
		que.pop();

		for (int ii = 0; ii < 4; ii++) { //이동
            
			int nextY = cur.y + dy[ii];
			int nextX = cur.x + dx[ii];

			if (nextY < 1 || nextX < 1 || nextY > 100 || nextX > 100)
				continue;//범위를 벗어남

			if (check[nextY][nextX] == true || light[nextY][nextX] == 0)
				continue;//이미 한번 방문 or 불이 켜지지 않은 곳


			check[nextY][nextX] = true;
			que.push({nextY, nextX});
            
			int switchCount = map[nextY][nextX].size();
			for (int i = 0; i < switchCount; i++) {
				pos temp = map[nextY][nextX][i];

				if (light[temp.y][temp.x] == 0)
				{
					lightcount++;
					light[temp.y][temp.x] += 1; //불킨다.
				}
			}


		}
	}


}


int main() {
    
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
        
		int x, y, a, b;

		cin >> x >> y >> a >> b;

		map[y][x].push_back({ b, a });
	}
	
	

	while (1) {
        
		int tempcount = lightcount;
		bfs({ 1, 1 }); // bfs 스위치 다 on 과 동시에 새로운 장소도 탐색한다.
		//누락되는게 있을수 있다. >> 그다음 bfs에서 처리될 것이므로 누락되는건 신경쓸필요 없다.
		//-> 종료조건은 추가되는 방이 없으면 종료함

		//종료조건
		if (lightcount == tempcount)
			break;

	}
	
	cout << lightcount;

	return 0;
}