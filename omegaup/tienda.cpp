#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli mod = 1e9 + 7;

lli inverse(lli a, lli m){
	lli r0 = a, r1 = m, ri, s0 = 1, s1 = 0, si;
	while(r1){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += m;
	return s0;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	string s;
	cin >> n >> s;
	vector<int> open(n), close(n);
	int sum = 0;
	for(int i = 0; i < n; ++i){
		sum += s[i] == 'A';
		open[i] = sum;
	}
	sum = 0;
	for(int i = n - 1; i >= 0; --i){
		sum += s[i] == 'V';
		close[i] = sum;
	}
	int limit = 2 * n + 10;
	vector<lli> fact(limit + 1, 1), inv(limit + 1, 1);
	for(int i = 1; i <= limit; ++i){
		fact[i] = fact[i - 1] * i % mod;
		inv[i] = inv[i - 1] * inverse(i, mod) % mod;
	}
	lli ans = 0;
	for(int i = 0; i < n; ++i){
		lli x = open[i], y = close[i] - 1;
		if(s[i] == 'A' && y >= 0){
			ans += fact[x + y] * inv[x] % mod * inv[y] % mod;
		}
	}
	cout << ans % mod;
	return 0;
}