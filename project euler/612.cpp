#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1000267129;

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ans;
}

const lli inv2 = power(2, mod*(mod-1) - 1);

int no(int allowed, int len){
	int sz = 0;
	if(allowed) sz = __builtin_popcount(allowed);
	if(sz == 0) return 0;
	int ans = 0;
	for(int d = 1; d <= len; ++d){
		lli tmp = power(sz, d-1);
		if(allowed & 1){
			tmp = tmp * (sz - 1) % mod;
		}else{
			tmp = tmp * sz % mod;
		}
		ans += tmp;
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int mem[20][20][1024][2];

int f(int len, int pos, int allowed, bool flg){
	if(pos == len){
		if(!flg) return 0;
		return no(allowed, len);
	}
	int & ans = mem[len][pos][allowed][flg];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		ans += f(len, pos+1, (flg | (d != 0)) ? (allowed & ~(1 << d)) : allowed, flg | (d != 0));
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	memset(mem, -1, sizeof(mem));
	for(int len = 1; len <= 18; ++len){
		lli tot = power(10, len) - 1;
		lli ans = (tot * (tot - 1) % mod - f(len, 0, 1023, 0)) * inv2 % mod;
		if(ans < 0) ans += mod;
		cout << "f(" << len << ") = " << ans << "\n";
	}
	return 0;
}