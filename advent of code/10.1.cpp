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
	nums.push_back(mx+3);
	sort(nums.begin(), nums.end());
	int curr = 0;
	vector<int> difs(4);
	for(int i = 0; i < nums.size(); ++i){
		int diff = nums[i] - curr;
		difs[diff]++;
		curr = nums[i];
	}
	cout << difs[1]*difs[3] << "\n";
	return 0;
}