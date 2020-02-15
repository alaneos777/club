#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<lli> mult(const vector<lli> & a, const vector<lli> & b){
	vector<lli> c(a.size() + b.size() - 1);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			c[i + j] += a[i] * b[j];
		}
	}
	return c;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	cin >> s;
	vector<lli> ans = {1};
	for(int i = 0; i < s.size()-1; ++i){
		if(s[i] != s[i+1]){
			ans = mult(ans, {1, -2*i-3});
		}
	}
	if((s[0] == 'H' && ans.back() < 0) || (s[0] == 'A' && ans.back() > 0)){
		for(lli & pi : ans){
			pi = -pi;
		}
	}
	cout << ans.size()-1 << "\n";
	for(int i = 0; i < ans.size(); ++i){
		if(i) cout << " ";
		cout << ans[i];
	}
	cout << "\n";
	return 0;
}