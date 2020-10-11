#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

int d[13];
int price[4];
int ans;

void dfs(int start, int cnt) {
	if (start > 12) {
		ans = min(ans, cnt);
		return;
	}
	dfs(start + 1, cnt + price[0] * d[start]);
	dfs(start + 1, cnt + price[1]);
	dfs(start + 3, cnt + price[2]);
	dfs(start + 12, cnt + price[3]);
}

int main() {
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		ans = 987654321;
		memset(d, 0, sizeof(d));
		memset(price, 0, sizeof(price));
		for (int i = 0; i < 4; i++) {
			cin >> price[i];
		}
		for (int i = 1; i <= 12; i++) {
			cin >> d[i];
		}
		dfs(1, 0);
		cout << "#" << test << " " << ans << endl;
	}
}
