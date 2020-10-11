#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, K, ans, fuel;
int map[21][21]; // 샤크 움직이는 맵
int id[21][21]; // 냄새에 아이디쓰기
int smell[21][21]; // 냄새들이 있는 맵.
bool visited[21][21];
int dx[] = { 0,-1,1,0,0 };
int dy[] = { 0,0,0,-1,1 }; // 상하좌우

struct shark {
	bool live;
	int num; // 상어 넘버
	int x, y;
	int dir; // 방향
	int c_dir[5][5]; // 방향들 우선순위
};

struct shark S[21 * 21];

void move() {
	//높은 아이디 순으로 무브 함.
	//빈칸이 있는지, 없으면 자신의냄새있는칸
	//현재 방향 체크하고 그 방향에서 우선순위대로
	//움직인다.k+1이라고 smell에 적고, id도 적음.
	//다음 상어움직임
	//빈칸이아니다(smell혹은 id보고 안다)
	//다움직이면 충돌여부 검사.가장 작은아이디인애만 남게.
	//전체적인 smell초 하나씩 줄임(smell이 0보다 클때.)
	vector <pair<pair<int, int>, int>> emp[21*21];
	for (int i = M; i >= 1; i--) {
		if (S[i].live) {
			int x = S[i].x;
			int y = S[i].y;
			for (int j = 1; j <= 4; j++) {
				int rx = x + dx[j];
				int ry = y + dy[j];
				if (rx < 0 || ry < 0 || rx >= N || ry >= N) continue;
				if (smell[rx][ry] == 0) {
					emp[i].push_back({ { rx, ry }, j });
				}
			}
			if (emp[i].size() == 0) {
				for (int j = 1; j <= 4; j++) {
					int rx = x + dx[j];
					int ry = y + dy[j];
					if (rx < 0 || ry < 0 || rx >= N || ry >= N) continue;
					if (id[rx][ry] == i) {
						emp[i].push_back({ { rx, ry }, j });
					}
				}
			}
		}
	}

	for (int i = M; i >= 1; i--) {
		if (S[i].live) {
			int dir = S[i].dir;
			int check = 0;
			for (int j = 1; j <= 4; j++) { // 방향 우선순위
				for (int k = 0; k < emp[i].size(); k++) {
					if (S[i].c_dir[dir][j] == emp[i][k].second) {
						S[i].dir = S[i].c_dir[dir][j];
						map[S[i].x][S[i].y] = 0;
						S[i].x = emp[i][k].first.first;
						S[i].y = emp[i][k].first.second;
						//cout << i << S[i].x << endl;
						map[S[i].x][S[i].y] = i;
						smell[S[i].x][S[i].y] = K + 1;
						id[S[i].x][S[i].y] = i;
						check = 1;
						break;
					}
				}
				if (check == 1) break;
			}
		}
	}
	for (int j = 0; j < N; j++) {
		for (int k = 0; k < N; k++) {
			if (smell[j][k] > 0) {
				smell[j][k]--;
			}
		}
	}
	for (int j = 0; j < N; j++) {
		for (int k = 0; k < N; k++) {
			if (smell[j][k] == 0) {
				id[j][k] = 0;
			}
		}
	}
	for (int i = M; i >= 1; i--) {
		bool check = false;
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				if (map[j][k] == i) {
					check = true;
				}
			}
		}
		if(check == false) S[i].live = false;
	}
}

int main() {
	cin >> N >> M >> K;
	ans = 0;
	fuel = K;
	memset(map, 0, sizeof(map));
	memset(id, 0, sizeof(id));
	memset(smell, 0, sizeof(smell));
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);



	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			
			if (map[i][j] > 0) {
				S[map[i][j]].live = true;
				S[map[i][j]].x = i; S[map[i][j]].y = j;
				id[i][j] = map[i][j];
				smell[i][j] = K;
			}
		}
	}
	for (int i = 1; i <= M; i++) {
		int dir;
		cin >> dir;
		S[i].dir = dir;
	}
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 4; k++) {
				cin >> S[i].c_dir[j][k];
			}
		}
	} // 방향 우선순위

	for (int time = 1; time <= 1000; time++) {
		move();

		int check = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] > 1) check = 1;
			}
		}
		if (check == 0) {
			ans = time; break;
		}
		if (check == 1 && time == 1000) {
			ans = -1; break;
		}
	}

	cout << ans << endl;
}
