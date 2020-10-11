#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, K, ans, fuel;
int map[21][21];
bool visited[21][21];
int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };

struct man {
	int start_x, start_y, end_x, end_y;
};

struct info {
	int start_x, start_y, dist, num;
};

struct man P[21 * 21]; // 그냥 사람정보
struct info D[21 * 21]; // 타는 사람 정보
int car_x, car_y;

bool info_cmp(info A, info B) {
	if (A.dist <= B.dist) {
		if (A.dist == B.dist) {
			if (A.start_x <= B.start_x) {
				if (A.start_x == B.start_x) {
					if (A.start_y < B.start_y) {
						return true;
					}
					return false;
				}
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

int find_shortest_man() { // 가까운 손님찾기
	memset(visited, false, sizeof(visited));
	queue <pair<pair<int, int>, pair<int, int>>> q;
	q.push(make_pair(make_pair(car_x, car_y), make_pair(0, fuel)));
	visited[car_x][car_y] = true;
	vector <info> v;
	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int dis = q.front().second.first;
		int nam_fuel = q.front().second.second;
		q.pop();
		if (map[x][y] >= 1) v.push_back({ x,y,dis,map[x][y] });
		if (nam_fuel == 0) continue;

		for (int i = 0; i < 4; i++) {
			int rx = x + dx[i];
			int ry = y + dy[i];
			if (rx < 0 || ry < 0 || rx >= N || ry >= N) continue;
			if (map[rx][ry] != -1 && visited[rx][ry] == false) {
				visited[rx][ry] = true;
				q.push(make_pair(make_pair(rx, ry), make_pair(dis+1, nam_fuel-1)));
			}
		}
	}

	if (v.size() == 0) return -1;

	sort(v.begin(), v.end(), info_cmp);
	map[v[0].start_x][v[0].start_y] = 0;
	fuel = fuel - v[0].dist;
	return v[0].num;
}

bool bfs(int s_x, int s_y, int e_x, int e_y, int num) { // 손님이동
	memset(visited, false, sizeof(visited));
	queue <pair<pair<int, int>, pair<int, int>>> q;
	q.push(make_pair(make_pair(s_x, s_y), make_pair(0, fuel)));
	visited[s_x][s_y] = true;
	
	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int dis = q.front().second.first;
		int nam_fuel = q.front().second.second;
		q.pop();
		
		if (x == e_x && y == e_y) {
			fuel = fuel - dis;
			fuel = fuel + 2 * dis;
			car_x = e_x; car_y = e_y;
			return true;
		}
		if (nam_fuel == 0) return false;

		for (int i = 0; i < 4; i++) {
			int rx = x + dx[i];
			int ry = y + dy[i];
			if (rx < 0 || ry < 0 || rx >= N || ry >= N) continue;
			if (map[rx][ry] != -1 && visited[rx][ry] == false) {
				visited[rx][ry] = true;
				q.push(make_pair(make_pair(rx, ry), make_pair(dis + 1, nam_fuel - 1)));
			}
		}
	}
	return false;
}

void Solution() {
	for (int i = 0; i < M; i++) { // 최대 손님수만큼만 움직임
		int num = find_shortest_man();
		if (num == -1) {
			ans = -1;
			return;
		}

		bool move = bfs(P[num].start_x, P[num].start_y, P[num].end_x, P[num].end_y, num);
		if (move == false) {
			ans = -1;
			return;
		}

	}
	ans = fuel;
	return;

}

int main() {
	cin >> N >> M >> K;
	ans = 0;
	fuel = K;
	memset(map, 0, sizeof(map));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) map[i][j] = -1;
		}
	}
	cin >> car_x >> car_y;
	car_x--; car_y--;
	//출발 행,열 도착 행,열
	for (int i = 1; i <= M; i++) {
		int start_x, start_y, end_x, end_y;
		cin >> start_x >> start_y >> end_x >> end_y;
		start_x--; start_y--; end_x--; end_y--;
		P[i] = { start_x, start_y, end_x, end_y };
		map[start_x][start_y] = i;
	}
	Solution();
	cout << ans << endl;
}
