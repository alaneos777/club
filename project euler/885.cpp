#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli mod = 1123455689;

map<array<int8_t, 9>, lli> mem[20];

lli S(int pos, array<int8_t, 9> freqs){
	if(pos == 0){
		lli ans = 0;
		for(int d = 1; d <= 9; ++d){
			while(freqs[d-1]--){
				ans = ans*10 + d;
			}
		}
		return ans % mod;
	}
	if(mem[pos].count(freqs)) return mem[pos][freqs];
	lli ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(d) freqs[d-1]++;
		ans += S(pos-1, freqs);
		if(d) freqs[d-1]--;
		if(ans >= mod) ans -= mod;
	}
	return mem[pos][freqs] = ans;
}

int main(){
	int N = 18;
	lli ans = S(N, array<int8_t, 9>());
	cout << ans << "\n";
	return 0;
}