#include <bits/stdc++.h>
using namespace std;

vector<set<int>> comb(const vector<int> & conj, int r){
	int n = conj.size();
	vector<int> tmp(r);
	vector<set<int>> ans;
	function<void(int, int)> comb = [&](int index, int i){
		if(index == r){
			set<int> data(tmp.begin(), tmp.end());
			ans.push_back(data);
		}else if(i < n){
			tmp[index] = conj[i];
			comb(index + 1, i + 1);
			comb(index, i + 1);
		}
	};
	comb(0, 0);
	return ans;
}

set<int> sq = {1, 4, 9, 16, 25, 36, 49, 64, 81};

bool valid(set<int> a, set<int> b){
	if(a.count(6)) a.insert(9);
	if(a.count(9)) a.insert(6);
	if(b.count(6)) b.insert(9);
	if(b.count(9)) b.insert(6);
	set<int> tmp;
	for(const int & ai : a){
		for(const int & bi : b){
			if(sq.count(10*ai + bi)){
				tmp.insert(10*ai + bi);
			}
			if(sq.count(10*bi + ai)){
				tmp.insert(10*bi + ai);
			}
		}
	}
	return tmp == sq;
}

int main(){
	auto sets = comb({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 6);
	int sz = sets.size();
	int ans = 0;
	for(int i = 0; i < sz; ++i){
		for(int j = i; j < sz; ++j){
			ans += valid(sets[i], sets[j]);
		}
	}
	cout << ans << "\n";
	return 0;
}