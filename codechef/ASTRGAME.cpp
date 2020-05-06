#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int mex(const vector<int> & a){
	int n = a.size();
	vector<bool> is(n);
	for(int ai : a){
		if(ai < n){
			is[ai] = true;
		}
	}
	for(int i = 0; i < n; ++i){
		if(!is[i]) return i;
	}
	return n;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		string s;
		int n;
		cin >> s >> n;
		int sz = s.size();
		vector<vector<int>> appears(sz);
		for(int i = 0; i < n; ++i){
			string word;
			cin >> word;
			int pos = s.find(word);
			while(pos != string::npos){
				appears[pos].push_back(word.size());
				pos = s.find(word, pos + 1);
			}
		}
		
		vector<vector<int>> mem(sz, vector<int>(sz, -1));
		
		function<int(int, int)> g = [&](int l, int r){
			if(r < 0 || l >= sz) return 0;
			if(mem[l][r] != -1) return mem[l][r];
			vector<int> reachable;
			for(int start = l; start <= r; ++start){
				for(int len : appears[start]){
					int end = start + len - 1;
					if(end <= r){
						reachable.push_back(g(l, start-1) ^ g(end+1, r));
					}
				}
			}
			return mem[l][r] = mex(reachable);
		};

		if(g(0, sz-1)){
			cout << "Teddy\n";
		}else{
			cout << "Tracy\n";
		}
	}
	return 0;
}