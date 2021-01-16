#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

lli ncr[51][51];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ncr[0][0] = 1;
	for(int i = 1; i <= 50; ++i){
		ncr[i][0] = ncr[i][i] = 1;
		for(int j = 1; j < i; ++j){
			ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
		}
	}
	int n, k;
	cin >> n >> k;
	vector<lli> p(n);
	for(lli & pi : p){
		cin >> pi;
	}
	sort(p.begin(), p.end(), greater<lli>());
	vector<lli> sums(n);
	partial_sum(p.begin(), p.end(), sums.begin());
	lli a, b;
	cin >> a >> b;
	function<lli(int, int, lli)> f = [&](int pos, int rem_k, lli rem_w){
		if(rem_k == 0) return 1ll;
		if(pos == n) return 0ll;
		if(sums[n-1] - (pos > 0 ? sums[pos-1] : 0) <= rem_w) return ncr[n - pos][rem_k];
		lli ans = f(pos + 1, rem_k, rem_w);
		if(rem_w >= p[pos]) ans += f(pos + 1, rem_k - 1, rem_w - p[pos]);
		return ans;
	};
	cout << f(0, k, b) - f(0, k, a-1) << "\n";
	return 0;
}