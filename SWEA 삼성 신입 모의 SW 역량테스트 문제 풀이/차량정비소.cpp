#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
int n, m, k, a, b; // ������� ���� â�� ��, ���� â�� ��, �� ��, Ÿ�� ���� â�� ��ȣ, Ÿ�� ���� â�� ��ȣ
vector<int> aTime, bTime; // aTime : �� ���� â���� ó���ϴ� �� �ɸ��� �ð�  // bTime : �� ���� â��
vector<pair<int,int>> aWork, bWork; // aWork : ����â�� first : ������ �ð�, second : ���� �ϰ� �ִ� �� ��ȣ // bWork �� ���� â���� ���ؼ�
struct customer { // �� �մԿ� ���ؼ�
	int aNum; // ����� ���� â�� ��ȣ
	int bNum; // ����� ���� â�� ��ȣ
	int sTime; // ���� �ð�
};
vector<customer> cus; // �մ� ����

void find() {
	int curTime = 0; // ���� �ð�
	int out = 0; // ��� ���� ����ģ ����� ��
	queue<int> aq; // ���� â���� ��ٸ��� �� ��ȣ ť
	queue<int> bq; // ���� â���� ��ٸ��� �� ��ȣ ť
	aWork.assign(n, { -1,-1 }); // �ش� ���� â���� �ƹ��� ������ first ������ -1 �� �ִ´�.
	bWork.assign(m, { -1,-1 }); // �ش� ���� â���� �ƹ��� ������ first ������ -1 �� �ִ´�.

	while (1) {

		for (int i = 0; i < k; i++) {
			if (cus[i].sTime == curTime) // ���� �ð��̸� aq ť�� �߰��Ѵ�.
				aq.push(i);
		}

		for (int i = 0; i < n; i++) { // ������ ���ÿ� ������ �� �ִ� ��찡 �ֱ⿡ ���� ������ �ִ� ���꺸�� ���� �ؾ��Ѵ�.
			if (aWork[i].first == curTime) { // ���� â���� �� �� �ð��̸� 
				aWork[i].first = -1; // ���� �� ���� â���� �����.
				bq.push(aWork[i].second); // �׸��� �� ���� â���� ���� ���� ���� â�� ��� ť(bq) �� ����.
			}
		}

		for (int i = 0; i < n; i++) {
			if (aq.empty()) // ��ٸ��� ���� ������ �������� �ʴ´�.
				break;
			if (aWork[i].first == -1) { // �� â���� ���ؼ� ���������
				aWork[i].first = curTime + aTime[i]; // ��� �ð��� ������Ʈ�ϰ�
				aWork[i].second = aq.front(); // �� �� ���� �� â���� �̿��ϴ��� ������Ʈ�ϰ�
				cus[aq.front()].aNum = i; // �ش� ���� �̿� â���� ������Ʈ�ϰ� 
				aq.pop(); // ť���� ������.
			}
		}

		// ���� â���� ���� ���� â���� ���� ������ �˰��� �̴�.

		for (int i = 0; i < m; i++) {
			if (bWork[i].first == curTime) {
				bWork[i].first = -1;
				out++; // ���� ��� ���μ����� �������Ƿ� �Ϸ�� �ο� ���� out �� �����ش�.
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

		if (out == k) // ��� ����� �Ϸ� �Ǿ����� while ���� �����ش�.
			break;

		curTime++; // ���� �ð��� ������Ʈ �Ѵ�.

	}

}

int main() {

	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int T;
	cin >> T; // �ݺ� Ƚ�� 

	for (int t = 1; t <= T; t++) {

		int ans = 0;

		cin >> n >> m >> k >> a >> b;
		aTime.assign(n, 0);
		bTime.assign(m, 0);
		customer tempCus; // cus �� �ʱ�ȭ �ϱ� ���ؼ� ������ ���� ��.
		cus.assign(k, tempCus);
		for (int i = 0; i < n; i++)
			cin >> aTime[i];
		for (int i = 0; i < m; i++)
			cin >> bTime[i];
		for (int i = 0; i < k; i++)
			cin >> cus[i].sTime;

		find();

		for (int i = 0; i < k; i++) {
			if (cus[i].aNum == a - 1 && cus[i].bNum == b - 1) // ������ 1�� ���� â���� �ִµ� ���� 0�� ���ͷ� Ǯ���⿡ -1 �� ���ش�.
				ans += (i + 1); // ���������� �� ��ȣ�� 1�� ���� �������� �ʰ�, 0�� ���� �����߱⿡ �� ��ȣ�� +1 �� ���ش�.
		}

		if (ans == 0) // � ���� ������ -1 �� ����ؾ� �Ѵ�.
			ans = -1;

		cout << "#" << t << " " << ans << endl;
	}

	return 0;
}

