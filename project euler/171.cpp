#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1e9;

const int M = 20;

int mem_f[M+1][2000];
int mem_g[M+1][2000];
lli ten[M+1];
bool isSq[2000];

int f(int pos, int sq_sum){
	if(pos == M){
		return isSq[sq_sum];
	}
	int & ans = mem_f[pos][sq_sum];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		ans += f(pos + 1, sq_sum + d*d);
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int g(int pos, int sq_sum){
	if(pos == M) return 0;
	int & ans = mem_g[pos][sq_sum];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		ans = (d * ten[M-1 - pos] % mod * f(pos + 1, sq_sum + d*d) % mod + g(pos + 1, sq_sum + d*d) + ans) % mod;
	}
	return ans;
}

int main(){
	memset(mem_f, -1, sizeof(mem_f));
	memset(mem_g, -1, sizeof(mem_g));
	for(int i = 1; i*i < 2000; ++i){
		isSq[i*i] = true;
	}
	ten[0] = 1;
	for(int i = 1; i <= M; ++i){
		ten[i] = ten[i-1] * 10 % mod;
	}
	cout << g(0, 0) << "\n";
	return 0;
}