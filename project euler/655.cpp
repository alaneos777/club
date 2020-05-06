#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const int mod = 1e7 + 19;
const int M = 32;
int ten[M+1];
int mem[M/2+4][mod];

int dp(int idx, int len, int rem){
	if(idx == (len + 1) / 2){
		return rem == 0;
	}
	int & ans = mem[idx][rem];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		int next = rem + d * ten[idx];
		if(idx != len-1 - idx){
			next += d * ten[len-1 - idx];
		}
		next %= mod;
		ans += dp(idx+1, len, next);
	}
	return ans;
}

int main(){
	lli ans = -2;
	ten[0] = 1;
	for(int i = 1; i <= M; ++i){
		ten[i] = ten[i-1] * 10ll % mod;
	}
	for(int len = M-1; len <= M; ++len){
		memset(mem, -1, sizeof(mem));
		ans += dp(0, len, 0);
	}
	cout << ans << "\n";
	return 0;
}