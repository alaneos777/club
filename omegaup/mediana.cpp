#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> nums(n);
	for(int i = 0; i < n; ++i){
		cin >> nums[i];
	}
	sort(nums.begin(), nums.end());
	if(n & 1) cout << fixed << setprecision(1) << 1.0 * nums[n/2] << "\n";
	else cout << fixed << setprecision(1) << 0.5*(nums[n/2-1] + nums[n/2]) << "\n";
	return 0;
}