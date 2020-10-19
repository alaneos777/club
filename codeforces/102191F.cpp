#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using ld = __float128;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<lli> a(n), b(n);
	for(lli & ai : a){
		cin >> ai;
	}
	partial_sum(a.begin(), a.end(), b.begin());
	auto acum = [&](int i, int j){
		return b[j] - (i ? b[i-1] : 0);
	};
	vector<int> res(n, -1);
	vector<ld> mem(n);
	function<ld(int)> f = [&](int i){
		if(i == n) return __float128(0);
		if(res[i] != -1) return mem[i];
		ld & ans = mem[i];
		int r = -1;
		for(int j = i; j < n && j <= i+5; ++j){
			ld take = logl(acum(i, j)) + f(j+1);
			if(j == i || take > ans){
				ans = take;
				r = j;
			}
		}
		res[i] = r;
		return ans;
	};
	f(0);
	int lo = 0;
	while(lo < n){
		int hi = res[lo];
		for(int i = lo; i <= hi; ++i){
			if(i > lo) cout << " ";
			cout << a[i];
		}
		lo = hi+1;
		if(lo < n) cout << " / ";
	}
	cout << "\n";
	return 0;
}