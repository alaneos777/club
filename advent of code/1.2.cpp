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
	bool found = false;
	for(int x : nums){
		if(found) break;
		for(int y : nums){
			int z = 2020 - x - y;
			if(table.count(z)){
				cout << x*y*z << "\n";
				found = true;
				break;
			}
		}
	}
	return 0;
}