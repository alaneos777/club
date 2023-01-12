#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b&1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	vector<int> S(163);
	for(int i = 1; i < 163; ++i){
		int res = powerMod(i, 81, 163);
		if(res == 162) res = -1;
		S[i] = res;
	}
	partial_sum(S.begin(), S.end(), S.begin());

	lli N = 1e16;
	lli ans = 0;
	lli i = 1;
	while(i <= N){
		lli ni = N/i, nxt = N/ni;
		ans += S[ni%163] * (nxt - i + 1);
		i = nxt + 1;
	}
	ans *= 2;
	cout << ans << "\n";
	return 0;
}