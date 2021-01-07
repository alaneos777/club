#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	string line;
	cin >> line;
	deque<int> nums;
	for(char c : line){
		nums.push_back(c-'0');
	}
	for(int k = 1; k <= 100; ++k){
		int a = nums.front(); nums.pop_front();
		int b = nums.front(); nums.pop_front();
		int c = nums.front(); nums.pop_front();
		int d = nums.front(); nums.pop_front();
		nums.push_front(a);
		int target = a-1;
		if(target == 0) target = 9;
		int idx = -1;
		while(true){
			auto pos = find(nums.begin(), nums.end(), target);
			if(pos != nums.end()){
				idx = pos-nums.begin();
				break;
			}
			target--;
			if(target == 0) target = 9;
		}
		nums.insert(nums.begin() + idx+1, b);
		nums.insert(nums.begin() + idx+2, c);
		nums.insert(nums.begin() + idx+3, d);
		a = nums.front(); nums.pop_front(); nums.push_back(a);
	}
	auto pos = find(nums.begin(), nums.end(), 1);
	rotate(nums.begin(), pos, nums.end());
	for(int i = 1; i < nums.size(); ++i){
		cout << nums[i];
	}
	cout << endl;
	return 0;
}