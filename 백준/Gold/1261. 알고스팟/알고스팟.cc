#include <iostream>
#include <deque>

using namespace std;

int dist[555][555]; // 벽을 부순 횟수의 의미 + 방문 여부 의미
int map[555][555];

int n, m; 

int dy[] = {1,-1,0,0};
int dx[] = {0,0,1,-1};

void bfs() {
    // 사실.. 대륙간 다리 놓기 문제와 비슷하게 풀이할 수 도 있을듯..?
    //
    // deque 를 이용해서 벽을 안부수는 경우에 우선적으로 탐색되게 하여 que 에 비용이 0 인 좌표들로 가득채우고..
    // 이후 벽을 한개 부숴야하는 경우가 탐색되고 두개.. 세개.. 부숴야하는 좌표들이 탐색된다.
    // 그리고 한번 탐색이된 좌표는 다시 탐색 및 dist 업데이트가 없으므로 dist 에 적재되는 값은 항상 벽 부수기의 최소값이다.
    
    deque<pair<int,int>> q;
    q.push_back(make_pair(0, 0));
    
    dist[0][0] = 0;
    
    while (!q.empty()) {
        
        int y = q.front().first;
        int x = q.front().second;
        q.pop_front();
        
        for (int k = 0; k < 4; k++) {
            
            int ny = y + dy[k];
            int nx = x + dx[k];
            
            if (ny < 0 || nx < 0 || ny >= n || nx >= m) {
                continue;
            }
            
            if (dist[ny][nx] != -1) {
                continue; // 이미 한번 방문했거나 벽을 부수면 업데이트가 되어 -1 이 아니다.
            }
            
            if (map[ny][nx] == 0) { // 빈칸
                dist[ny][nx] = dist[y][x];
                q.push_front(make_pair(ny, nx)); // push front, 가장 우선적으로 이동
            } else { // 벽
                dist[ny][nx] = dist[y][x] + 1;
                q.push_back(make_pair(ny, nx)); // push back, 벽을 깨고 이동하는 것이므로 후 순위
            }
        }
    }
}

int main() {
    
    cin >> m >> n;

    for (int i = 0; i < n; i++) {
        
        string s;
        cin >> s;
        
        for (int j = 0; j < m; j++) {
            
            if (s[j] == '0')
                map[i][j] = 0; // 빈칸
            else
                map[i][j] = 1; // 벽
            
            dist[i][j] = -1;
        }
    }
    
    bfs();
    
    printf("%d\n", dist[n-1][m-1]);
    
    return 0;
}
