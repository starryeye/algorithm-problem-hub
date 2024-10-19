#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int map[26][26];
bool check[26][26];
int n;

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int indexcount;

struct Point {
	int y, x, tick;
};

void dfs(Point node) {
    
	check[node.y][node.x] = true;

	if (map[node.y][node.x] == 1)
		indexcount++;

	for (int i = 0; i < 4; i++) {
        
		int y = node.y + dy[i];
		int x = node.x + dx[i];

		if (y < 0 || y >= n || x < 0 || x >= n)
			continue;

		if (check[y][x] == true || map[y][x] == 0)
			continue;
        
		dfs({ y, x, node.tick + 1 });
	}
}


int main() {
    
	vector<int> sol;
	cin >> n;

	for (int i = 0; i < n; i++) {
        
        string str;
		cin >> str;
        
		for (int j = 0; j < n; j++) {
            
			if (str[j] == '0')
				map[i][j] = 0;
			else
				map[i][j] = 1;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
            
			if (check[i][j] == false && map[i][j] ==1) {
                
				Point p = { i, j, 0 };
				dfs(p);

				if (indexcount != 0) {
                    
					sol.push_back(indexcount);
					indexcount = 0;
				}
			}
		}
	}


	sort(sol.begin(), sol.end());
	cout << sol.size() << endl;
    
	for (int i = 0; i < sol.size(); i++) {
		cout << sol[i] << endl;
	}

	return 0;
}