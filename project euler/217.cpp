#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 14348907; // 3^15

const int M = 47;
int mem_f[M+1][1000];
int mem_g[M+1][1000];
lli ten[M+1];

int f(int size, int pos = 0, int sum = 0){
	if(pos == size) return sum == 0;
	int& ans = mem_f[pos][sum+500];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(pos == 0 && d == 0) continue;
		int sgn = pos < size/2 ? 1 : -1;
		if(2*pos + 1 == size) sgn = 0;
		ans += f(size, pos+1, sum + d*sgn);
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int g(int size, int pos = 0, int sum = 0){
	if(pos == size) return 0;
	int& ans = mem_g[pos][sum+500];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(pos == 0 && d == 0) continue;
		int sgn = pos < size/2 ? 1 : -1;
		if(2*pos + 1 == size) sgn = 0;
		ans += (ten[size-1-pos] * d % mod * f(size, pos+1, sum + d*sgn) + g(size, pos+1, sum + d*sgn)) % mod;
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	ten[0] = 1;
	for(int i = 1; i <= M; ++i){
		ten[i] = 10ll * ten[i-1] % mod;
	}
	int ans = 0;
	for(int size = 1; size <= M; ++size){
		memset(mem_f, -1, sizeof(mem_f));
		memset(mem_g, -1, sizeof(mem_g));
		ans += g(size);
		if(ans >= mod) ans -= mod;
	}
	cout << ans << "\n";
	return 0;
}