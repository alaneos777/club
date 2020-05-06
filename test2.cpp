#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<lli> s(n), v(n);
	for(lli & si : s){
		cin >> si;
	}
	for(lli & vi : v){
		cin >> vi;
	}
	int sz_lhs = n/2, sz_rhs = n - sz_lhs;
	vector<pair<lli, int>> lhs;
	for(int m = 0; m < (1 << sz_lhs); ++m){
		lli sum = 0;
		for(int i = 0; i < sz_lhs; ++i){
			if(m & (1 << i)){
				sum += s[i];
			}else{
				sum -= v[i];
			}
		}
		lhs.emplace_back(sum, m);
	}
	sort(lhs.begin(), lhs.end());
	pair<lli, lli> ans = {numeric_limits<lli>::max(), 0};
	for(int m = 0; m < (1 << sz_rhs); ++m){
		lli sum = 0;
		for(int i = 0; i < sz_rhs; ++i){
			if(m & (1 << i)){
				sum += s[sz_lhs + i];
			}else{
				sum -= v[sz_lhs + i];
			}
		}
		int pos = lower_bound(lhs.begin(), lhs.end(), make_pair(-sum, -1)) - lhs.begin();
		for(int i = max(0, pos-1); i <= pos+1 && i < lhs.size(); ++i){
			ans = min(ans, make_pair(abs(sum + lhs[i].first), lhs[i].second | (lli(m) << sz_lhs)));
		}
	}
	cout << ans.first << "\n";
	vector<int> ans_lhs, ans_rhs;
	for(int i = 0; i < n; ++i){
		if(ans.second & (1ll << i)){
			ans_lhs.push_back(i);
		}else{
			ans_rhs.push_back(i);
		}
	}
	cout << ans_lhs.size();
	for(int x : ans_lhs){
		cout << " " << x+1;
	}
	cout << "\n" << ans_rhs.size();
	for(int x : ans_rhs){
		cout << " " << x+1;
	}
	cout << "\n";
	return 0;
}