#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	string str;
	cin >> str;
	stringstream ss(str);
	vector<int> nums;
	int x;
	while(getline(ss, str, ',')){
		nums.push_back(stoi(str));
	}
	map<int, pair<int, int>> mem;
	for(int i = 1; i <= nums.size(); ++i){
		mem[nums[i-1]] = {i, 0};
	}
	int last = nums.back();
	for(int i = nums.size()+1; i <= 2020; ++i){
		if(mem[last].second == 0){
			mem[0] = {i, mem[0].first};
			last = 0;
		}else{
			int dif = mem[last].first - mem[last].second;
			mem[dif] = {i, mem[dif].first};
			last = dif;
		}
	}
	cout << last << endl;
	return 0;
}