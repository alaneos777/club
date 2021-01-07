#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	vector<lli> nums;
	lli x;
	while(cin >> x){
		nums.push_back(x);
	}
	vector<lli> acum(nums.size());
	partial_sum(nums.begin(), nums.end(), acum.begin());
	for(int k = 25; k < nums.size(); ++k){
		set<lli> valid;
		for(int i = k-25; i < k; ++i){
			for(int j = i+1; j < k; ++j){
				valid.insert(nums[i] + nums[j]);
			}
		}
		if(valid.count(nums[k]) == 0){
			for(int start = 0; start < nums.size(); ++start){
				for(int end = start+1; end < nums.size(); ++end){
					if(acum[end] - (start == 0 ? 0 : acum[start-1]) == nums[k]){
						lli mini = *min_element(nums.begin() + start, nums.begin() + end+1);
						lli maxi = *max_element(nums.begin() + start, nums.begin() + end+1);
						cout << mini+maxi << "\n";
						break;
					}
				}
			}
			break;
		}
	}
	return 0;
}