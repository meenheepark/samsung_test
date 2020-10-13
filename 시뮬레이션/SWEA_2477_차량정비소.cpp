#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int T, N, M, K, A, B, ans, cnt;

struct s_A { // 접수
	int time; // 처리시간
	int num; //쓰고있는 손님 넘버
	int end_time; // 끝나는시간
	bool ok; // 사용가능한지
};

struct s_B { // 정비
	int time;
	int num;
	int end_time;
	bool ok;
};

struct person { // 정비
	int time; // 접수에 도착하는시간
	int a_num;
	int b_num;
	int a_end_time;
	int b_end_time;
};

struct s_A a[10];
struct s_B b[10];
struct person p[1001];
queue <int> a_q;//a기다리는 큐
queue <int> b_q; // b기다리는 큐

void check(int t) {
	for (int i = 1; i <= K; i++) {
		if (p[i].time == t) {
			a_q.push(i);
		}
	}

	for (int i = 1; i <= N; i++) {
		if (a[i].ok == false && a[i].end_time <= t) {
			//cout << a[i].num <<"ddd" << endl;
			a[i].ok = true;
			b_q.push(a[i].num);
		}
	}

	for (int i = 1; i <= M; i++) {
		if (b[i].ok == false && b[i].end_time <= t) {
			b[i].ok = true;
			cnt++;
		}
	}
}

int main() {
	cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N >> M >> K >> A >> B;
		ans = 0;
		for (int i = 1; i <= N; i++) {
			cin >> a[i].time;
			a[i].ok = true; a[i].end_time = -1;
		}
		for (int i = 1; i <= M; i++) {
			cin >> b[i].time;
			b[i].ok = true; b[i].end_time = -1;
		}
		for (int i = 1; i <= K; i++) {
			cin >> p[i].time;
		}
		cnt = 0;
		int t = 0;
		while (1) {
			
			check(t); // 끝난게 있는지 검사.
			if (cnt == K) break;

			while (!a_q.empty()) {
				bool ch = false;
				for (int i = 1; i <= N; i++) {
					if (a[i].ok == true) {
						ch = true;
						a[i].num = a_q.front();
						a[i].end_time = a[i].time + t;
						a[i].ok = false;
						p[a_q.front()].a_num = i;
						a_q.pop();
						break;
					}
				}
				if (ch == false) break; // 다찼다.
			}

			/*=============================================*/

			while (!b_q.empty()) {
				bool ch = false;
				for (int i = 1; i <= M; i++) {
					if (b[i].ok == true) {
						ch = true;
						b[i].num = b_q.front();
						b[i].end_time = b[i].time + t;
						b[i].ok = false;
						p[b_q.front()].b_num = i;
						b_q.pop();
						break;
					}
				}
				if (ch == false) break; // 다찼다.
			}
			t++;
		}

		for (int i = 1; i <= K; i++) {
			//cout << p[i].a_num << p[i].b_num << endl;
			if (p[i].a_num == A && p[i].b_num == B) {
				ans += i;
			}
		}
		if (ans == 0) ans = -1;
		cout << "#" << test << " " << ans << endl;
	}
}
