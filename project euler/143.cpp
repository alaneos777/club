#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int L = 120000;
	vector<vector<int>> pairs(L+1);
	for(int n = 1; n*n <= L; ++n){
		for(int m = n+1; m*m + m*n + n*n <= L; ++m){
			if(__gcd(m, n) == 1 && (m - n) % 3 != 0){
				int a = m*m + m*n + n*n;
				int b = 2*m*n + n*n;
				int c = m*m - n*n;
				if(b >= c) swap(b, c);
				for(int k = 1; a*k <= L; ++k){
					pairs[b*k].push_back(c*k);
				}
			}
		}
	}
	for(auto& p : pairs){
		sort(p.begin(), p.end());
	}
	set<int> st;
	for(int p = 1; p <= L; ++p){
		int sz = pairs[p].size();
		for(int i = 0; i < sz; ++i){
			for(int j = i+1; j < sz; ++j){
				int q = pairs[p][i];
				int r = pairs[p][j];
				assert(q<r);
				if(binary_search(pairs[q].begin(), pairs[q].end(), r)){
					if(p+q+r <= L) st.insert(p+q+r);
				}
			}
		}
	}
	lli ans = 0;
	for(int x : st){
		ans += x;
	}
	cout << ans << "\n";
	return 0;
}