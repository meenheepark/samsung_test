#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

int T, N, ans = 987654321;
int map[17][17];
int c[17];

void cal() {
	vector <int> a;
	vector <int> b;
	for (int i = 0; i < N; i++) {
		if (c[i] == 0) a.push_back(i);
		else b.push_back(i);
	}
	int sum_a = 0;
	for (int i = 0; i < N / 2; i++) {
		for (int j = i + 1; j < N / 2; j++) {
			sum_a += map[a[i]][a[j]] + map[a[j]][a[i]];
		}
	}

	int sum_b = 0;
	for (int i = 0; i < N / 2; i++) {
		for (int j = i + 1; j < N / 2; j++) {
			sum_b += map[b[i]][b[j]] + map[b[j]][b[i]];
		}
	}

	ans = min(ans, abs(sum_a - sum_b));
}

void dfs(int idx, int cnt) {
	if (idx == N) return;
	if (cnt == N / 2) {
		cal();
		return;
	}

	dfs(idx + 1, cnt);
	c[idx] = 1;
	dfs(idx + 1, cnt+1);
	c[idx] = 0;
}

int main() {
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N;
		ans = 987654321;
		memset(c, 0, sizeof(c));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		dfs(0, 0);

		cout << "#" << test << " " << ans << endl;
	}
}
