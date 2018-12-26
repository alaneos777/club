#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 9;
const lli x = 59;
const int M = 1e6 + 10;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

const lli inv_x = powerMod(x, mod-2, mod);

int conv(char c){
	if('a' <= c && c <= 'z') return c - 'a';
	return c - 'A' + 26;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	vector<lli> pots(M + 1, 1);
	for(int i = 1; i <= M; ++i){
		pots[i] = pots[i - 1] * x % mod;
	}
	while(cin >> s){
		string srev = s;
		reverse(srev.begin(), srev.end());
		lli hash = 0, hashrev = 0;
		int n = s.size();
		for(int i = 0; i < n; ++i){
			hash = (hash + conv(s[i]) * pots[i] % mod) % mod;
		}
		for(int i = 0; i < n; ++i){
			hashrev = (hashrev + conv(srev[i]) * pots[i] % mod) % mod;
		}
		if(hash == hashrev){
			cout << s << "\n";
			continue;
		}
		int ans = n;
		lli hash_o = hash;
		lli hashrev_o = hashrev;
		for(int i = n; i >= 1; --i){
			lli curr = (hash_o + hashrev * pots[n] % mod) % mod;
			lli currrev = (hash + hashrev_o * pots[i] % mod) % mod;
			if(currrev == curr){
				ans = min(ans, i);
			}
			hashrev = (hashrev - conv(s[i-1])) * inv_x % mod;
			hash = (hash - conv(s[i-1]) * pots[i-1] % mod) % mod;
			if(hash < 0) hash += mod;
			if(hashrev < 0) hashrev += mod;
		}
		cout << s;
		for(int i = ans-1; i >= 0; --i){
			cout << s[i];
		}
		cout << "\n";
	}
	return 0;
}