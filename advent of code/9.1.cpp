#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	vector<lli> nums;
	lli x;
	while(cin >> x){
		nums.push_back(x);
	}
	for(int k = 25; k < nums.size(); ++k){
		set<lli> valid;
		for(int i = k-25; i < k; ++i){
			for(int j = i+1; j < k; ++j){
				valid.insert(nums[i] + nums[j]);
			}
		}
		if(valid.count(nums[k]) == 0){
			cout << nums[k] << "\n";
			break;
		}
	}
	return 0;
}