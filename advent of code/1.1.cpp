#include <bits/stdc++.h>
using namespace std;

int main(){
	vector<int> nums;
	int x;
	while(cin >> x){
		nums.push_back(x);
	}
	unordered_set<int> table;
	for(int x : nums){
		table.insert(x);
	}
	for(int x : nums){
		int y = 2020 - x;
		if(table.count(y)){
			cout << x*y << "\n";
			break;
		}
	}
	return 0;
}
