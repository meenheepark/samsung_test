#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>

using namespace std;

int T, D, W, K, ans;
int map[14][21];

bool check(int map[14][21]) {
	bool r = true;
	for (int i = 0; i < W; i++) {
		int cnt = 1; bool t = true;
		for (int j = 0; j < D-1; j++) {
			if (map[j+1][i] == map[j][i]) {
				cnt++;
				if (cnt >= K) {
					t = true; break;
				}
			}
			else if(map[j+1][i] != map[j][i]){
				cnt = 1;
				t = false;
				if ( D - 1 - j < K) break;
			}
		}
		if (t) r = true;
		else {
			r = false; return r;
		}
	}
	return r;
}

void dfs(int row, int cnt) {
	if (K == 1) {
		ans = 0; return;
	}
	if (check(map) == true) {
		ans = min(ans, cnt);
	}

	if (row == D || cnt == K) return;

	int tmp[14][21];
		for (int j = 0; j < W; j++) {
			tmp[row][j] = map[row][j];
		}


	dfs(row + 1, cnt);//안바꾸고 넘어감.

	for (int j = 0; j < W; j++) {
		map[row][j] = 0;
	}
	dfs(row + 1, cnt +1);
	
	for (int j = 0; j < W; j++) {
		map[row][j] = 1;
	}
	dfs(row + 1, cnt + 1);
	for (int j = 0; j < W; j++) {
		map[row][j] = tmp[row][j];
	}
}


int main() {
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> D >> W >> K;
		ans = 987654321;
		memset(map, 0, sizeof(map));
		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				cin >> map[i][j];
			}
		}

		dfs(0, 0);

		cout << "#" << test << " " << ans << endl;
	}
}
