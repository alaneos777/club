#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

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
	int n, k, m;
	cin >> n >> k;
	vector<lli> t(n+1), math(n+1), economy(n+1), f(n+1), g(n+1);
	for(int i = 1; i <= n; ++i){
		cin >> t[i];
	}
	for(int i = 1; i <= n; ++i){
		int ai;
		cin >> ai;
		if(t[i] == 1) math[i] = ai;
		else economy[i] = ai;
	}
	partial_sum(math.begin(), math.end(), math.begin());
	partial_sum(economy.begin(), economy.end(), economy.begin());
	for(int i = 0; i <= n; ++i){
		f[i] = math[i] - economy[i];
		g[i] = f[i] + k;
	}

	unordered_map<lli, vector<int>> wt_f, wt_g;
	for(int i = 0; i <= n; ++i){
		wt_f[f[i]].push_back(i);
		wt_g[g[i]].push_back(i);
	}
	cin >> m;
	vector<query> queries;
	for(int i = 0; i < m; ++i){
		int l, r;
		cin >> l >> r;
		queries.emplace_back(l-1, r, i);
	}
	sort(queries.begin(), queries.end());

	vector<lli> answers(m);
	lli ans = 0;
	int prevL = 0, prevR = -1;
	for(const query& q : queries){
		for(int i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			//equal to g[i] in f[i+1,...,prevR]
			const auto& arr = wt_f[g[i]];
			ans -= upper_bound(arr.begin(), arr.end(), prevR) - lower_bound(arr.begin(), arr.end(), i+1);
		}
		for(int i = prevL - 1; i >= q.l; --i){
			//equal to g[i] in f[i+1,...,prevR]
			const auto& arr = wt_f[g[i]];
			ans += upper_bound(arr.begin(), arr.end(), prevR) - lower_bound(arr.begin(), arr.end(), i+1);
		}
		for(int i = max(prevR + 1, q.l); i <= q.r; ++i){
			//equal to f[i] in g[q.l,...,i-1]
			const auto& arr = wt_g[f[i]];
			ans += upper_bound(arr.begin(), arr.end(), i-1) - lower_bound(arr.begin(), arr.end(), q.l);
		}
		for(int i = prevR; i >= q.r + 1; --i){
			//equal to f[i] in g[q.l,...,i-1]
			const auto& arr = wt_g[f[i]];
			ans -= upper_bound(arr.begin(), arr.end(), i-1) - lower_bound(arr.begin(), arr.end(), q.l);
		}
		answers[q.index] = ans;
		prevL = q.l, prevR = q.r;
	}

	for(lli x : answers){
		cout << x << "\n";
	}
	return 0;
}