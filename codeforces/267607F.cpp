#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 1e8 + 7;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

vector<int> kmp(const vector<bool> & pattern){
	vector<int> pi(pattern.size());
	int i = 1, j = 0;
	while(i < pattern.size()){
		if(pattern[i] == pattern[j])
			pi[i++] = ++j;
		else{
			if(j == 0) pi[i++] = 0;
			else j = pi[j - 1];
		}
	}
	return pi;
}

const int n = 360000;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int s, p;
	while(cin >> s >> p){
		if(s == -1 && p == -1) break;
		vector<bool> circle(n);
		for(int i = 0; i < p; ++i){
			int a;
			cin >> a;
			circle[a] = 1;
		}
		vector<int> pi = kmp(circle);
		int len = (n % (n - pi.back()) == 0 ? n - pi.back() : n);
		int cnt = n / len;
		vector<int> acum(n);
		for(int i = 0; i < n; ++i){
			acum[i] = circle[i];
			if(i) acum[i] += acum[i-1];
		}
		lli ans = 0;
		for(int i = 0; i < n; i += len){
			ans += power(s, acum[__gcd(i, n) - 1]);
			if(ans >= mod) ans -= mod;
		}
		ans = ans * power(cnt, mod-2) % mod;
		cout << ans << "\n";
	}
	return 0;
}