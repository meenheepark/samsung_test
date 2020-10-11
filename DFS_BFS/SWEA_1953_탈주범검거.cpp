#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N, M, R, C, L, ans;
int map[51][51];
int time2[53][53];

void bfs(int a, int b) {
	queue <pair<int, int>> q;
	q.push(make_pair(a, b));
	time2[a][b] = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		int rx, ry, n;
		if (time2[x][y] == L ) continue;
		if (map[x][y] == 1) {
			//상
			rx = x - 1; ry = y; n = map[rx][ry];
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0 && (n == 1 || n == 2 || n == 5 || n == 6)) {
					time2[rx][ry] = time2[x][y] + 1;
					q.push(make_pair(rx, ry ));
			}
			//하
			rx = x + 1; ry = y; n = map[rx][ry];
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0 && (n == 1 || n == 2 || n == 4 || n == 7)) {
					time2[rx][ry] = time2[x][y] + 1;
					q.push(make_pair( rx, ry ));

			}

			//좌
			rx = x; ry = y-1; n = map[rx][ry];
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0 && (n == 1 || n == 3 || n == 4 || n == 5)) {

					time2[rx][ry] = time2[x][y] + 1;
					q.push({ rx, ry });

			}
			//우
			rx = x; ry = y+1;
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
				n = map[rx][ry];
				if (n == 1 || n == 3 || n == 6 || n == 7) {
					time2[rx][ry] = time2[x][y] + 1;
					q.push({ rx, ry });
				}
			}
			
		}
		else if (map[x][y] == 2) {
			//상
			rx = x - 1; ry = y;
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
				n = map[rx][ry];
				if (n == 1 || n == 2 || n == 5 || n == 6) {
					time2[rx][ry] = time2[x][y] + 1;
					q.push({ rx, ry });
				}
			}
			//하
			rx = x + 1; ry = y;
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
				n = map[rx][ry];
				if (n == 1 || n == 2 || n == 4 || n == 7) {
					time2[rx][ry] = time2[x][y] + 1;
					q.push({ rx, ry });
				}
			}

		}
		else if (map[x][y] == 3) {
				//좌
				rx = x; ry = y - 1;
				if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
					n = map[rx][ry];
					if (n == 1 || n == 3 || n == 4 || n == 5) {
						time2[rx][ry] = time2[x][y] + 1;
						q.push({ rx, ry });
					}
				}

				//우
				rx = x; ry = y + 1;
				if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
					n = map[rx][ry];
					if (n == 1 || n == 3 || n == 6 || n == 7) {
						time2[rx][ry] = time2[x][y] + 1;
						q.push(make_pair(rx, ry ));
					}
				}

		}
		else if (map[x][y] == 4) {
				//상
				rx = x - 1; ry = y; n = map[rx][ry];
				if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
					if (n == 1 || n == 2 || n == 5 || n == 6) {
						time2[rx][ry] = time2[x][y] + 1;
						q.push(make_pair(rx, ry ));
					}
				}
				//우
				rx = x; ry = y + 1; n = map[rx][ry];
				if (rx >=0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0 && (map[rx][ry] == 1 || map[rx][ry] == 3 || map[rx][ry] == 6 || map[rx][ry] == 7)) {
						time2[rx][ry] = time2[x][y] + 1;
						q.push(make_pair( rx, ry ));

				}
		}
		else if (map[x][y] == 5) {
			//하
			rx = x + 1; ry = y;
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
				n = map[rx][ry];
				if (n == 1 || n == 2 || n == 4 || n == 7) {
					time2[rx][ry] = time2[x][y] + 1;
					q.push({ rx, ry });
				}
			}
				//우
				rx = x; ry = y + 1;
				if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
					n = map[rx][ry];
					if (n == 1 || n == 3 || n == 6 || n == 7) {
						time2[rx][ry] = time2[x][y] + 1;
						q.push({ rx, ry });
					}
				}
		}
		else if (map[x][y] == 6) {
			//하
			rx = x + 1; ry = y;
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
				n = map[rx][ry];
				if (n == 1 || n == 2 || n == 4 || n == 7) {
					time2[rx][ry] = time2[x][y] + 1;
					q.push({ rx, ry });
				}
			}
			
			//좌
			rx = x; ry = y - 1;
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0) {
				n = map[rx][ry];
				if (n == 1 || n == 3 || n == 4 || n == 5) {
					time2[rx][ry] = time2[x][y] + 1;
					q.push({ rx, ry });
				}
			}

		}
		else if (map[x][y] == 7) {
			//상
			rx = x - 1; ry = y; n = map[rx][ry];
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0 && (n == 1 || n == 2 || n == 5 || n == 6)) {
					time2[rx][ry] = time2[x][y] + 1;
					q.push({ rx, ry });

			}
			//좌
			rx = x; ry = y - 1; n = map[rx][ry];
			if (rx >= 0 && ry >= 0 && rx < N && ry < M && time2[rx][ry] == 0&& (n == 1 || n == 3 || n == 4 || n == 5)) {
				time2[rx][ry] = time2[x][y] + 1;
				q.push({ rx, ry });
			}
		}
	}
}

int main() {
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		ans = 0;
		memset(map, 0, sizeof(map));
		memset(time2, 0, sizeof(time2));

		cin >> N >> M >> R >> C >> L;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> map[i][j];
			}
		}
		bfs(R, C);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (time2[i][j] > 0) {
					ans++;
				}
			}
		}
		
		cout << "#" << test << " " << ans << endl;
	}
}
