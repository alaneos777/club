#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 6;

int main(){
	int sz = 1 << M;
	vector<int> pi(sz);
	for(int n = 0; n < sz; ++n){
		int out = (n << 1) & (sz - 1);
		out |= (((n >> 5) & 1) ^ (((n >> 4) & 1) & ((n >> 3) & 1)));
		pi[n] = out;
	}
	vector<bool> vis(sz);
	vector<int> lens;
	for(int n = 0; n < sz; ++n){
		if(!vis[n]){
			int cnt = 0;
			int u = n;
			do{
				cnt++;
				vis[u] = true;
				u = pi[u];
			}while(u != n);
			lens.push_back(cnt);
		}
	}
	sort(lens.begin(), lens.end());
	vector<lli> L(lens.back() + 1);
	L[0] = 2, L[1] = 1;
	for(int i = 2; i < L.size(); ++i){
		L[i] = L[i-1] + L[i-2];
	}
	lli ans = 1;
	for(int len : lens){
		ans *= L[len];
	}
	cout << ans << "\n";
	return 0;
}