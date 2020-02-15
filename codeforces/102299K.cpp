#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<lli> nums(n);
	for(lli & num : nums){
		cin >> num;
	}
	sort(nums.begin(), nums.end());
	lli ans = 1;
	for(int i = 0; i < n && nums[i] <= ans; ++i){
		ans += nums[i];
	}
	cout << ans << "\n";
	return 0;
}