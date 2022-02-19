#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;

lli powerMod(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

int ncr(int n, int r){
	if(r < 0 || r > n) return 0;
	r = min(r, n-r);
	lli num = 1, den = 1;
	for(int i = 1; i <= r; ++i){
		num = num * (n-r+i) % mod;
		den = den * i % mod;
	}
	return num * powerMod(den, mod-2) % mod;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	int s = 0;
	for(int i = 0; i < n; ++i){
		int ai;
		cin >> ai;
		s += ai;
	}
	int N = m+n, R = n+s;
	cout << ncr(N, R) << "\n";
	return 0;
}