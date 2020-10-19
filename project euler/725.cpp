#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int N = 2020;
const lli mod = 1e16;

lli ten[N+1];
lli mem_f[N+1][19][10];
lli mem_g[N+1][19][10];

lli f(int pos, int sum, int maxi){
	if(pos == N) return sum == 2*maxi;
	if(sum > 18) return 0;
	lli & ans = mem_f[pos][sum][maxi];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		ans += f(pos+1, sum+d, max(maxi, d));
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

lli g(int pos, int sum, int maxi){
	if(pos == N) return 0;
	if(sum > 18) return 0;
	lli & ans = mem_g[pos][sum][maxi];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		ans += ((ten[N-1 - pos] ? (__int128)d * ten[N-1 - pos] * f(pos+1, sum+d, max(maxi, d)) % mod : 0) + g(pos+1, sum+d, max(maxi, d)));
		while(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	memset(mem_f, -1, sizeof(mem_f));
	memset(mem_g, -1, sizeof(mem_g));
	ten[0] = 1;
	for(int i = 1; i <= N; ++i){
		ten[i] = ten[i-1] * 10 % mod;
	}
	cout << g(0, 0, 0) << "\n";
	return 0;
}