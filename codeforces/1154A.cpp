#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<lli> nums(4);
	for(lli & n : nums){
		cin >> n;
	}
	sort(nums.begin(), nums.end());
	lli sum = nums[3];
	cout << sum-nums[0] << " " << sum-nums[1] << " " << sum-nums[2] << "\n";
	return 0;
}