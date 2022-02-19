#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for(int& ai : a){
		cin >> ai;
		ai %= m;
	}
	auto gen = [&](int l, int r){
		vector<int> ans = {0};
		for(int i = l; i <= r; ++i){
			int sz = ans.size();
			for(int j = 0; j < sz; ++j){
				int s = ans[j] + a[i];
				if(s >= m) s -= m;
				ans.push_back(s);
			}
		}
		sort(ans.begin(), ans.end());
		return ans;
	};
	auto lhs = gen(0, n/2);
	auto rhs = gen(n/2+1, n-1);
	int ans = 0;
	for(int ai : lhs){
		int pos = upper_bound(rhs.begin(), rhs.end(), m-1-ai) - rhs.begin();
		pos--;
		if(0 <= pos && pos < rhs.size()){
			ans = max(ans, ai + rhs[pos]);
		}
		pos = upper_bound(rhs.begin(), rhs.end(), 2*m-1-ai) - rhs.begin();
		pos--;
		if(0 <= pos && pos < rhs.size()){
			ans = max(ans, ai + rhs[pos] - m);
		}
	}
	cout << ans << "\n";
	return 0;
}