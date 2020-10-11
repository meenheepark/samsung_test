#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

int N, K, ans;
int map[9][9];
int max_num = 0;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

void dfs(int x, int y, int cnt) {

	int check = 0;
	for (int i = 0; i < 4; i++) {
		int rx = x + dx[i];
		int ry = y + dy[i];
		if (rx < 0 || ry < 0 || rx >= N || ry >= N) continue;
		if (map[x][y] > map[rx][ry]) {
			check = 1;
		}
	}
	if (check == 0) {
		ans = max(ans, cnt);
		return;
	}

	for (int i = 0; i < 4; i++) {
		int rx = x + dx[i];
		int ry = y + dy[i];
		if (rx < 0 || ry < 0 || rx >= N || ry >= N) continue;
		if (map[x][y] > map[rx][ry]) { 
			dfs(rx, ry, cnt + 1);
		}
	}
}

int main() {
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N >> K;
		ans = 0;
		max_num = 0;
		memset(map, 0, sizeof(map));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] > max_num) max_num = map[i][j];
			}
		}
		vector <pair<int, int>> v;
 		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == max_num) {
					v.push_back({i,j});
				}
			}
		}
		for (int k = 1; k <= K; k++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					map[i][j] -= k;
					for (int r = 0; r < v.size(); r++) {
						dfs(v[r].first, v[r].second, 1);
					}
					map[i][j] += k;
				}
			}
		}
 
		cout << "#" << test << " " << ans << endl;
	}
}
