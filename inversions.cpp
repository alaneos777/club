#include <bits/stdc++.h>
using namespace std;

int merge(vector<int> & nums, int i, int m, int j, vector<int> & tmp){
	int pos1 = i, pos2 = m, pos3 = i;
	int ans = 0;
	while(pos1 < m && pos2 <= j){
		if(nums[pos1] <= nums[pos2]){
			tmp[pos3++] = nums[pos1++];
		}else{
			tmp[pos3++] = nums[pos2++];
			ans += m - pos1;
		}
	}
	while(pos1 < m){
		tmp[pos3++] = nums[pos1++];
	}
	while(pos2 <= j){
		tmp[pos3++] = nums[pos2++];
	}
	for(int pos = i; pos <= j; pos++){
		nums[pos] = tmp[pos];
	}
	return ans;
}

int inversions(vector<int> & nums, int i, int j, vector<int> & tmp){
	int ans = 0;
	if(i < j){
		int m = i + ((j - i) >> 1);
		ans += inversions(nums, i, m, tmp);
		ans += inversions(nums, m + 1, j, tmp);
		ans += merge(nums, i, m + 1, j, tmp);
	}
	return ans;
}

int inversions(vector<int> & nums){
	int ans = 0;
	int n = nums.size();
	for(int i = 0; i < n - 1; i++){
		for(int j = i + 1; j < n; j++){
			if(nums[i] > nums[j]) ans++;
		}
	}
	return ans;
}

int main(){
	vector<int> nums;
	int num;
	while(cin >> num){
		nums.push_back(num);
	}
	int n = nums.size();
	vector<int> tmp(n);
	cout << inversions(nums) << "\n";
	return 0;
}