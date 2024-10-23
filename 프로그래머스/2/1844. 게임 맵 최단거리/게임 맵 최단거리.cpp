#include<vector>
#include<queue>
using namespace std;

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

struct pos {
    int y, x;
    
    pos(int _y, int _x) : y(_y), x(_x) {
    }
};

int bfs(vector<vector<int>>& maps, vector<vector<bool>>& check, pos start, pos target) {
    
    queue<pos> que;
    
    que.push(start);
    check[start.y][start.x] = true;
    
    int result = 1; // start 지점 부터 세아림
    while(!que.empty()) {
        
        int queSize = que.size();
        for (int qs = 0; qs < queSize; qs++) {
            
            int cy = que.front().y;
            int cx = que.front().x;
            que.pop();
            
            if (cy == target.y && cx == target.x) {
                return result;
            }
            
            for (int i = 0; i < 4; i++) {
                
                int ny = cy + dy[i];
                int nx = cx + dx[i];
                
                if (ny < 0 || nx < 0 || ny >= maps.size() || nx >= maps[0].size()) {
                    continue;
                }
                
                if (maps[ny][nx] == 0) { // 벽
                    continue;
                }
                
                if (check[ny][nx] == true) { // 이미 방문
                    continue;
                }
                
                que.push({ny, nx});
                check[ny][nx] = true;
            }
            
        }
        
        result++;
    }
    
    return -1;
}

int solution(vector<vector<int>> maps) {
    
    int n = maps.size();
    int m = maps[0].size();
    
    vector<vector<bool>> check(maps.size(), vector<bool>(maps[0].size(), false));
    
    return bfs(maps, check, {0, 0}, {n - 1, m - 1});
}