#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

int T, K, ans;
int c[5][8];

void count() {
	if (c[1][0] == 1) {
		ans += 1;
	}
	if (c[2][0] == 1) {
		ans += 2;
	}
	if (c[3][0] == 1) {
		ans += 4;
	}
	if (c[4][0] == 1) {
		ans += 8;
	}
}

void turn(int num, int dir) {
	int tmp[8];
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < 8; i++) {
		tmp[i] = c[num][i];
		//cout << c[num][i];
	}
	//cout << endl;

	if (dir == 1) { // 시계방향
		for (int i = 1; i < 8; i++) {
			c[num][i] = tmp[i-1];
		}
		c[num][0] = tmp[7];
	}
	else { // 반시계방향
		for (int i = 0; i < 7; i++) {
			c[num][i] = tmp[i + 1];
		}
		c[num][7] = tmp[0];
	}

}

void move(int num, int dir) {
	vector <pair<int, int>> v;
	int d = dir;
	for (int i = num; i >= 2; i--) {
		if (c[i][6] != c[i - 1][2] && d != 0) {
			if (d == 1) d = -1;
			else d = 1;
			v.push_back({ i-1, d });
		}
		if (c[i][6] == c[i - 1][2]) {
			d = 0;
		}
	}
	d = dir;
	for (int i = num; i <= 3; i++) {
		if (c[i][2] != c[i + 1][6] && d != 0) {
			if (d == 1) d = -1;
			else d = 1;
			v.push_back({ i+1, d });
		}
		if (c[i][2] == c[i + 1][6]) {
			d = 0;
		}
	}
	v.push_back({ num, dir });
	for (int i = 0; i < v.size(); i++) {
		turn(v[i].first, v[i].second);
	}
}

int main() {
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> K;
		ans = 0;
		for (int i = 1; i <= 4; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> c[i][j];
			}
		}

		for (int i = 0; i < K; i++) {
			int num, dir;
			cin >> num >> dir;
			move(num, dir);
		}
		count();
		cout << "#" << test << " " << ans << endl;
	}
}
