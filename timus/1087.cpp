#include <bits/stdc++.h>
using namespace std;

int mex(const vector<int> & a){
	if(a.empty()) return 0;
	vector<bool> tmp(*max_element(a.begin(), a.end()) + 3);
	for(const int & x : a)
		tmp[x] = true;
	for(int i = 0; i < tmp.size(); ++i)
		if(!tmp[i]) return i;
	return 0;
}

int dp[10010], nums[55], m;

int grundy(int n){
	if(n == 0) return dp[n] = 1;
	int &ans = dp[n];
	if(ans != -1) return ans;
	vector<int> state;
	for(int i = 0; i < m; ++i){
		if(n >= nums[i]) state.push_back(grundy(n - nums[i]));
	}
	return ans = mex(state);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	fill(begin(dp), end(dp), -1);
	int n;
	cin >> n >> m;
	for(int i = 0; i < m; ++i){
		cin >> nums[i];
	}
	if(grundy(n)) cout << "1\n";
	else cout << "2\n";
	return 0;
}