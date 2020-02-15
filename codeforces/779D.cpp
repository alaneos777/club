#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string t, p;
	cin >> t >> p;
	vector<int> order(t.size());
	for(int & ai : order){
		cin >> ai;
	}

	auto can = [&](int m){
		string r;
		vector<bool> b(t.size(), true);
		for(int i = 0; i < m; ++i){
			b[order[i]-1] = false;
		}
		for(int i = 0; i < t.size(); ++i){
			if(b[i]) r += t[i];
		}
		int j = 0;
		for(int i = 0; i < r.size() && j < p.size(); ++i){
			if(p[j] == r[i]){
				++j;
			}
		}
		return j == p.size();
	};

	int l = 1, r = t.size();
	while(true){
		int m = (l + r) / 2;
		if(can(m)){
			if(can(m+1)){
				l = m+1;
			}else{
				cout << m << "\n";
				return 0;
			}
		}else{
			r = m-1;
		}
	}
	return 0;
}