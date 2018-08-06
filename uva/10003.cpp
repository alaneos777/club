#include <bits/stdc++.h>
using namespace std;

int l, n;
vector<int> cuts;
vector<vector<int>> mem;

int ans(int left, int right){
	if(left >= right) return 0;
	int &ret = mem[left][right];
	if(ret == -1){
		ret = 1 << 30;
		for(int i = 0; i < n; ++i){
			if(left <= cuts[i] && cuts[i] <= right){
				ret = min(ret, right - left + min(ans(left, cuts[i]), ans(cuts[i], right)));
			}
		}
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	while(cin >> l && l){
		cin >> n;
		cuts = vector<int>(n);
		mem = vector<vector<int>>(l + 1, vector<int>(l + 1, -1));
		for(int i = 0; i < n; ++i)
			cin >> cuts[i];
		cout << "The minimum cutting is " << ans(0, l) << ".\n";
	}
	return 0;
}