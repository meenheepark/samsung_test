#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int T, N, X, ans;
int map[21][21];
int check[21][21]; // 이미 경사로 만드렁ㅆ는지 확인하는 배열

void check_Row() {
	for (int i = 0; i < N; i++) {
		bool ok = true;
		for (int j = 0; j < N - 1; j++) {
			if (abs(map[i][j] - map[i][j+1]) > 1) {
				ok = false; continue;
			}
			if (map[i][j] < map[i][j + 1]) {
				int num = map[i][j];
				for (int k = j; k > j - X; k--) {
					if (map[i][k] != num) {
						ok = false; break;
					}
					if (check[i][k] == 1) {
						ok = false; break;
					}
				}
				if (ok == false) continue;
				if (ok != false) {
					for (int k = j; k > j - X; k--) {
						check[i][k] = 1;
					}
				}
			}
			
			if (map[i][j] > map[i][j + 1]) {
				int num = map[i][j+1];
				//cout << j << "j";
				for (int k = j + 1; k < j + 1 + X; k++) {
					if (map[i][k] != num) {
						//cout << i << j << endl;
						ok = false; break;
					}
					if (check[i][k] == 1) {
						ok = false; break;
					}
				}
				if (ok == false) continue;
				if (ok != false) {
					for (int k = j + 1; k < j + 1+ X; k++) {
						check[i][k] = 1;
					}
				}
			}
		}
		if (ok == true) {
			//cout << "r" << i << endl;
			ans++;
		}
	}

}

void check_Col () {
	for (int i = 0; i < N; i++) {
		bool ok = true;
		for (int j = 0; j < N - 1; j++) {
			if (abs(map[j][i] - map[j + 1][i]) > 1) {
				ok = false; continue;
			}
			if (map[j][i] < map[j+1][i]) {
				int num = map[j][i];
				for (int k = j; k > j - X; k--) {
					if (map[k][i] != num) {
						ok = false; break;
					}
					if (check[k][i] == 1) {
						ok = false; break;
					}
				}
				if (ok == false) continue;
				if (ok != false) {
					for (int k = j; k > j - X; k--) {
						check[k][i] = 1;
					}
				}
			}

			if (map[j][i] > map[j+1][i]) {
				int num = map[j+1][i];
				for (int k = j + 1; k < j + X + 1; k++) {
					if (map[k][i] != num) {
						ok = false; break;
					}
					if (check[k][i] == 1) {
						ok = false; break;
					}
				}
				if (ok == false) continue;
				if (ok != false) {
					for (int k = j + 1; k < j + 1 + X; k++) {
						check[k][i] = 1;
					}
				}
			}
		}
		if (ok == true) {
			//cout << "c" << i << endl;
			ans++;
		}
	}

}

int main() {
	cin >> T;
	for (int test = 1; test <= T; test++) {
		ans = 0;
		memset(check, 0, sizeof(check));
		cin >> N >> X;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		check_Row();
		memset(check, 0, sizeof(check));
		check_Col();



		
		cout << "#" << test << " " << ans << endl;
	}
}
