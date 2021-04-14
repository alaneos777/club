#include <bits/stdc++.h>
using namespace std;

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct query{
	int l, r, k, index;
	int64_t ord;
	query() {}
	query(int l, int r, int k, int index): l(l), r(r), k(k), index(index) {
		ord = gilbertOrder(l, r, 21, 0);
	}
	bool operator<(const query & q) const{
		return ord < q.ord;
	}
};

const int inf = 1e9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int aleatorio_int(int a, int b){
	uniform_int_distribution<int> dist(a, b);
	return dist(rng);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >>n >> q;
	vector<int> a(n);
	for(int& ai : a) cin >> ai;
	vector<query> queries;
	for(int i = 0; i < q; ++i){
		int l, r, k;
		cin >> l >> r >> k;
		queries.emplace_back(l-1, r-1, k, i);
	}

	sort(queries.begin(), queries.end());
	vector<int> answers(q);
	vector<int> freq(n+1);
	int prevL = 0, prevR = -1;

	auto add = [&](int x){
		freq[x]++;
	};

	auto remove = [&](int x){
		freq[x]--;
	};

	auto getAns = [&](int l, int r, int m){
		int ans = inf;
		for(int i = 1; i <= 80; ++i){
			int pos = aleatorio_int(l, r);
			if(freq[a[pos]] >= m){
				ans = min(ans, a[pos]);
			}
		}
		if(ans == inf) ans = -1;
		return ans;
	};

	for(const query& q : queries){
		for(int i = prevL, j = min(prevR, q.l - 1); i <= j; ++i) remove(a[i]);
		for(int i = prevL - 1; i >= q.l; --i) add(a[i]);
		for(int i = max(prevR + 1, q.l); i <= q.r; ++i) add(a[i]);
		for(int i = prevR; i >= q.r + 1; --i) remove(a[i]);
		answers[q.index] = getAns(q.l, q.r, (q.r - q.l + 1) / q.k + 1);
		prevL = q.l, prevR = q.r;
	}

	for(int ans : answers){
		cout << ans << "\n";
	}
	return 0;
}