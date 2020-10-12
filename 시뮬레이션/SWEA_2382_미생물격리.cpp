#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

int N, M, K;
int map[101][101];

struct cell {
	int x, y, dir, cnt;
	bool live;
};

struct cell c[1001];

int dx[] = { 0,-1,1,0,0};
int dy[] = { 0,0,0,-1,1};

void change(int num, int dir) { // 방향바꿔주는 함수
	if (dir == 1) {//상
		c[num].dir = 2;
	}
	else if (dir == 2) {
		c[num].dir = 1;
	}
	else if (dir == 3) {
		c[num].dir = 4;
	}
	else if (dir == 4) {
		c[num].dir = 3;
	}
}

int main() {
	int T;
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL); 
	cout.tie(NULL);

	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N >> M >> K;
		memset(map, 0, sizeof(map));
		vector <int> n_map[101][101];
		for (int i = 1; i <= K; i++) {
			int x, y, cnt, dir;
			cin >> c[i].x >> c[i].y >> c[i].cnt >> c[i].dir;
			c[i].live = true;
			n_map[c[i].x][c[i].y].push_back(i);
		}
		
		for (int time = 1; time <= M; time++) {
			for (int i = 1; i <= K; i++) {
				if (c[i].cnt == 0) continue;
				if (c[i].live == true) {
					int x = c[i].x; int y = c[i].y;
					int rx = x+dx[c[i].dir]; int ry = y+ dy[c[i].dir];
					if (rx == 0 || rx == N - 1 || ry == 0 || ry == N-1) {//약품지역에 갔다면.
						c[i].x = rx;
						c[i].y = ry;
						c[i].cnt /= 2;
						change(i, c[i].dir);
						if (c[i].cnt == 0) c[i].live = false;
					}
					else { // 안전한 곳 감.
						c[i].x = rx;
						c[i].y = ry;
						n_map[rx][ry].push_back(i);
					}
				}

			}
			//N*N을 안쓰도록 해여함.

			for (int j = 1; j <= K; j++) {
				int x = c[j].x;
				int y = c[j].y;
				//여러개있다면.
				int cnt = 0;
				int max_id = 0;
				int sum = 0;
				int num = 0;
				if (n_map[x][y].size() > 1) {
					for (int i = 0; i < n_map[x][y].size(); i++) {
						if (c[n_map[x][y][i]].live) {
							if (c[n_map[x][y][i]].x == x && c[n_map[x][y][i]].y == y) {
								if (c[n_map[x][y][i]].cnt > cnt) {
									cnt = c[n_map[x][y][i]].cnt;
									max_id = n_map[x][y][i];
								}
								sum += c[n_map[x][y][i]].cnt;
								c[n_map[x][y][i]].live = false;
							}
						}
					}
				}
				c[max_id].cnt = sum;
				c[max_id].live = true;
			}
		}

		int ans = 0;
		for (int i = 1; i <= K; i++) {
			if (c[i].live) {
				ans += c[i].cnt;
			}
		}

		
		cout << "#" << test << " " << ans << endl;
	}
}
