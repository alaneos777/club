#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
using ld = long double;
using pii = pair<ld, int>;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for(int & ai : a){
		cin >> ai;
	}
	auto f = [&](ld x){
		lli cuts = 0;
		for(int ai : a){
			cuts += (ai - 1) / x;
		}
		return cuts <= k;
	};
	int l = 1, r = 1e9, ans;
	while(l <= r){
		int m = (l + r) / 2;
		if(f(m)){
			ans = m;
			r = m - 1;
		}else{
			l = m + 1;
		}
	}
	cout << ans << "\n";
	return 0;
}