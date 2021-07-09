#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

template<typename T>
struct FenwickTree{
	int N;
	vector<T> bit;

	FenwickTree(int n): N(n){
		bit.resize(N);
	}

	void update(int pos, T value){
		while(pos < N){
			bit[pos] += value;
			pos |= pos + 1;
		}
	}

	T query(int r){
		T res = 0;
		while(r >= 0){
			res += bit[r];
			r = (r & (r + 1)) - 1;
		}
		return res;
	}

	T query(int l, int r){
		return query(r) - query(l - 1);
	}
};

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
	int l, r, index;
	int64_t ord;
	query() {}
	query(int l, int r, int index): l(l), r(r), index(index) {
		ord = gilbertOrder(l, r, 21, 0);
	}
	bool operator<(const query & q) const{
		return ord < q.ord;
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	map<int, vector<int>> mp;
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		mp[ai].push_back(i);
	}
	int val = 0;
	for(const auto&[ai, pos] : mp){
		for(int i : pos){
			a[i] = val;
		}
		val++;
	}
	vector<query> queries;
	for(int i = 0; i < q; ++i){
		int l, r;
		cin >> l >> r;
		queries.emplace_back(l, r-1, i);
	}
	sort(queries.begin(), queries.end());

	FenwickTree<lli> freq(n);
	lli invs = 0;

	auto remove_left = [&](int x){
		invs -= freq.query(0, x-1);
		freq.update(x, -1);
	};

	auto add_left = [&](int x){
		invs += freq.query(0, x-1);
		freq.update(x, 1);
	};

	auto add_right = [&](int x){
		invs += freq.query(x+1, n-1);
		freq.update(x, 1);
	};

	auto remove_right = [&](int x){
		invs -= freq.query(x+1, n-1);
		freq.update(x, -1);
	};

	vector<lli> answers(q);
	int prevL = 0, prevR = -1;

	for(const query& q : queries){
		for(int i = prevL, j = min(prevR, q.l - 1); i <= j; ++i) remove_left(a[i]);
		for(int i = prevL - 1; i >= q.l; --i) add_left(a[i]);
		for(int i = max(prevR + 1, q.l); i <= q.r; ++i) add_right(a[i]);
		for(int i = prevR; i >= q.r + 1; --i) remove_right(a[i]);
		answers[q.index] = invs;
		prevL = q.l, prevR = q.r;
	}

	for(lli ans : answers){
		cout << ans << "\n";
	}

	return 0;
}