#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;

lli mod = 1e9 + 7;

vector<lli> pot;

lli f(int s, lli n){
	if(n <= 0) return 0;
	lli ans = 0;
	for(int p = 0; p < s; p++){
		lli bitsOn = ((n + 1) / pot[s - p] * pot[s - p - 1] + max((lli)0, (n + 1) % pot[s - p] - pot[s - p - 1]));
		ans = (ans + bitsOn * pot[p]);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	pot.resize(32);
	pot[0] = 1;
	for(int i = 1; i < pot.size(); i++){
		pot[i] = pot[i - 1] << 1;
	}
	int s, k, l, r;
	cin >> s >> k;
	while(k--){
		cin >> l >> r;
		lli ans = (f(s, r) - f(s, l - 1)) % mod;
		if(ans < 0) ans += mod;
		cout << (int)ans << "\n";
	}
	return 0;
}