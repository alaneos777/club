#include <bits/stdc++.h>
using namespace std;

int main(){
	vector<int> nums;
	int x;
	int mx = 0;
	while(cin >> x){
		nums.push_back(x);
		mx = max(mx, x);
	}
	nums.push_back(0);
	nums.push_back(mx+3);
	sort(nums.begin(), nums.end());
	vector<int64_t> memo(nums.size()+1, -1);
	function<int64_t(int)> f = [&](int pos){
		if(pos+1 == nums.size()) return 1ll;
		int64_t & ans = memo[pos];
		if(ans != -1) return ans;
		ans = 0;
		for(int i = pos+1; i < nums.size(); ++i){
			if(nums[i] - nums[pos] <= 3) ans += f(i);
			else break;
		}
		return ans;
	};
	cout << f(0) << "\n";
	return 0;
}