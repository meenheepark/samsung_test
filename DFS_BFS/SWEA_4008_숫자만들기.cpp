#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N, ans;
int num[13];
int cal[4];
int min_ans = 987654321;
int max_ans = -987654321;

void dfs(int idx, int a[4], int sum) {
	if (idx == N) {
		min_ans = min(min_ans, sum);
		max_ans = max(max_ans, sum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (a[i] != 0) {
			if (i == 0) {
				a[i] -= 1;
				dfs(idx + 1, a, sum + num[idx]);
				a[i] += 1;
			}
			else if (i == 1) {
				a[i] -= 1;
				dfs(idx + 1, a, sum - num[idx]);
				a[i] += 1;
			}
			else if (i == 2) {
				a[i] -= 1;
				dfs(idx + 1, a, sum * num[idx]);
				a[i] += 1;
			}
			else if (i == 3) {
				a[i] -= 1;
				dfs(idx + 1, a, sum / num[idx]);
				a[i] += 1;
			}
		}
	}
}


int main() {
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++) {
		ans = 0;
		min_ans = 987654321;
		max_ans = -987654321;
		memset(num, 0, sizeof(num));
		memset(cal, 0, sizeof(cal));

		cin >> N;
		for (int i = 0; i < 4; i++) {
			cin >> cal[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> num[i];
		}
		dfs(1, cal, num[0]);
		ans = max_ans - min_ans;
		cout << "#" << test << " " << ans << endl;
	}
}
