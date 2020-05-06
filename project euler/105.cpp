#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int sum(const vector<int> & a){
	int ans = 0;
	for(int x : a){
		ans += x;
	}
	return ans;
}

bool valid(const vector<int> & a){
	int n = a.size();
	bool valid = true;
	for(int mask = 0; mask < (1 << n); ++mask){
		int sub = mask;
		while(sub > 0){
			vector<int> B, C;
			for(int i = 0; i < n; ++i){
				if(!(mask & (1 << i))) continue;
				if(sub & (1 << i)){
					B.push_back(a[i]);
				}else{
					C.push_back(a[i]);
				}
			}
			if(!B.empty() && !C.empty()){
				valid &= ((sum(B) != sum(C)) & ((!(B.size() > C.size())) | (sum(B) > sum(C))));
			}
			if(!valid) break;
			sub = (sub - 1) & mask;
		}
		if(!valid) break;
	}
	return valid;
}

int main(){
	lli ans = 0;
	ifstream in("p105_sets.txt");
	string str;
	while(getline(in, str)){
		stringstream ss(str);
		vector<int> conj;
		int ai;
		while(ss >> ai){
			conj.push_back(ai);
		}
		if(valid(conj)){
			ans += sum(conj);
		}
	}
	cout << ans << "\n";
	return 0;
}