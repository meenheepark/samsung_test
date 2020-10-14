#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int T, N, M, ans;
int map[21][21];
int cost[41];
int idx;
int k_map[41 + 100][41 + 100];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

struct home {
	int x, y;
};

struct home h[21 * 21];

void bfs(int x, int y,int k) {
	queue <pair<int, int>> q;
	q.push({ x ,y });
	k_map[x][y] = 1;
	while (!q.empty()) {
		int rx = q.front().first;
		int ry = q.front().second;
		q.pop();
		if (k_map[rx][ry] == k) continue;
		for (int i = 0; i < 4; i++) {
			int nx = rx + dx[i];
			int ny = ry + dy[i];
			if (k_map[nx][ny] == 0) {
				k_map[nx][ny] = k_map[rx][ry] + 1;
				q.push({ nx, ny });
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i <= 140 ; i++) {
		for (int j = 0; j <= 140 ; j++) {
			if (k_map[i][j] > 0) {
				cnt++;
			}
		}
	}
	cost[k] = cnt;
	return;
}

int cnt(int x, int y, int k) { // 해당 위치에서 거리 k이하인 집갯수
	int sum = 0;
	for (int i = 0; i < idx; i++) {
		int t;
		t = abs(h[i].x - x) + abs(h[i].y - y);
		//cout << t << endl;
		if (t <= k - 1) sum++;
	}
	return sum;
}

void search(int x, int y, int k) {
	//if (k == 2 * N + 1) return;
	int num = cnt(x, y, k);
	//cout << num << endl;
	int cal = num * M - cost[k];
	if (cal >= 0) {
		//cout << "kk" << endl;
		ans = max(ans, num);
	}
}

int main() {
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N >> M;
		ans = 0;
		memset(map, 0, sizeof(map));
		idx = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) {
					h[idx].x = i; h[idx].y = j; idx++;
				}
			}
		}
		for (int i = 1; i <= 2 * N; i++) {
			memset(k_map, 0, sizeof(k_map));
			bfs(N,N,i);
			//cout << cost[i] << " ";
		}
		//cout << cost[1] << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 1; k <= 2 * N - 2; k++) {
					search(i, j, k);
				}
			}
		}


		cout << "#" << test << " " << ans << endl;
	}
}
