#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
int n, m, k, a, b; // 순서대로 접수 창구 수, 정비 창구 수, 고객 수, 타겟 접수 창구 번호, 타겟 정비 창구 번호
vector<int> aTime, bTime; // aTime : 각 접수 창고에서 처리하는 데 걸리는 시간  // bTime : 각 정비 창구
vector<pair<int,int>> aWork, bWork; // aWork : 접수창구 first : 끝나는 시간, second : 현재 하고 있는 고객 번호 // bWork 는 정비 창구에 대해서
struct customer { // 각 손님에 대해서
	int aNum; // 사용한 접수 창구 번호
	int bNum; // 사용한 정비 창구 번호
	int sTime; // 도착 시간
};
vector<customer> cus; // 손님 벡터

void find() {
	int curTime = 0; // 현재 시각
	int out = 0; // 모든 일을 끝마친 사람의 수
	queue<int> aq; // 접수 창구를 기다리는 고객 번호 큐
	queue<int> bq; // 정비 창구를 기다리는 고객 번호 큐
	aWork.assign(n, { -1,-1 }); // 해당 접수 창구가 아무도 없으면 first 값으로 -1 을 넣는다.
	bWork.assign(m, { -1,-1 }); // 해당 정비 창구가 아무도 없으면 first 값으로 -1 을 넣는다.

	while (1) {

		for (int i = 0; i < k; i++) {
			if (cus[i].sTime == curTime) // 도착 시간이면 aq 큐에 추가한다.
				aq.push(i);
		}

		for (int i = 0; i < n; i++) { // 끝남과 동시에 시작할 수 있는 경우가 있기에 빼는 연산을 넣는 연산보다 빨리 해야한다.
			if (aWork[i].first == curTime) { // 접수 창구를 다 쓴 시간이면 
				aWork[i].first = -1; // 이제 이 접수 창구는 비었다.
				bq.push(aWork[i].second); // 그리고 이 접수 창구를 쓰던 고객은 정비 창구 대기 큐(bq) 로 들어간다.
			}
		}

		for (int i = 0; i < n; i++) {
			if (aq.empty()) // 기다리는 고객이 없으면 실행하지 않는다.
				break;
			if (aWork[i].first == -1) { // 각 창구에 대해서 비어있으면
				aWork[i].first = curTime + aTime[i]; // 사용 시간을 업데이트하고
				aWork[i].second = aq.front(); // 몇 번 고객이 이 창구를 이용하는지 업데이트하고
				cus[aq.front()].aNum = i; // 해당 고객의 이용 창구를 업데이트하고 
				aq.pop(); // 큐에서 뻬낸다.
			}
		}

		// 정비 창구도 위의 접수 창구와 거의 유사한 알고리즘 이다.

		for (int i = 0; i < m; i++) {
			if (bWork[i].first == curTime) {
				bWork[i].first = -1;
				out++; // 이제 모든 프로세스가 끝났으므로 완료된 인원 수인 out 을 더해준다.
			}
		}

		for (int i = 0; i < m; i++) {
			if (bq.empty())
				break;
			if (bWork[i].first == -1) {
				bWork[i].first = curTime + bTime[i];
				bWork[i].second = bq.front();
				cus[bq.front()].bNum = i;
				bq.pop();
			}
		}

		if (out == k) // 모든 사람이 완료 되었으면 while 문을 끝내준다.
			break;

		curTime++; // 현재 시간을 업데이트 한다.

	}

}

int main() {

	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int T;
	cin >> T; // 반복 횟수 

	for (int t = 1; t <= T; t++) {

		int ans = 0;

		cin >> n >> m >> k >> a >> b;
		aTime.assign(n, 0);
		bTime.assign(m, 0);
		customer tempCus; // cus 를 초기화 하기 위해서 임으로 만든 것.
		cus.assign(k, tempCus);
		for (int i = 0; i < n; i++)
			cin >> aTime[i];
		for (int i = 0; i < m; i++)
			cin >> bTime[i];
		for (int i = 0; i < k; i++)
			cin >> cus[i].sTime;

		find();

		for (int i = 0; i < k; i++) {
			if (cus[i].aNum == a - 1 && cus[i].bNum == b - 1) // 원래는 1번 부터 창구가 있는데 나는 0번 부터로 풀었기에 -1 씩 해준다.
				ans += (i + 1); // 마찬가지로 고객 번호도 1번 부터 시작하지 않고, 0번 부터 시작했기에 고객 번호에 +1 을 해준다.
		}

		if (ans == 0) // 어떤 고객도 없으면 -1 을 출력해야 한다.
			ans = -1;

		cout << "#" << t << " " << ans << endl;
	}

	return 0;
}

