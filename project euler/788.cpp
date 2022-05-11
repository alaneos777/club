#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 7;
int mem[2222][4444][2];

int f(int len, int D, int pos = 0, int freqD = 0, int total = 0, bool zeroPrefix = true){
	if(pos == len) return 2*freqD > total;
	int& ans = mem[pos][2*freqD - total + 2222][zeroPrefix];
	if(ans != -1) return ans;
	ans = 0;
	for(int i = 0; i <= 9; ++i){
		if(i == 0 && zeroPrefix){
			ans += f(len, D, pos+1, freqD, total, true);
		}else{
			ans += f(len, D, pos+1, freqD + (i==D), total+1, false);
		}
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

int main(){
	int n = 2022;
	memset(mem, -1, sizeof(mem));
	int ans = f(n, 0);
	memset(mem, -1, sizeof(mem));
	ans += f(n, 1)*9ll % mod;
	if(ans >= mod) ans -= mod;
	cout << ans << "\n";
	return 0;
}