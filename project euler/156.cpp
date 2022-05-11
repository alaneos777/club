#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli mem[11][2][11];

lli f(lli n, int d){
	memset(mem, -1, sizeof(mem));
	string s = to_string(n);
	function<lli(int, bool, int)> f = [&](int pos, bool canUseAll, int freq) -> lli{
		if(pos == s.size()) return freq;
		lli& ans = mem[pos][canUseAll][freq];
		if(ans != -1) return ans;
		ans = 0;
		int limit = canUseAll ? 9 : s[pos]-'0';
		for(int i = 0; i <= limit; ++i){
			ans += f(pos+1, canUseAll | (i < limit), freq + (i == d));
		}
		return ans;
	};
	return f(0, false, 0);
}

inline int sgn(lli x){
	if(x > 0) return 1;
	if(x < 0) return -1;
	return 0;
}

lli go(int d, lli l, lli r){
	if(l == r){
		if(f(l, d) == l){
			//cout << d << " " << l << "\n";
			return l;
		}else{
			return 0;
		}
	}else{
		lli fl = f(l, d), fr = f(r, d);
		if(sgn(fl - l) != sgn(fl - r) || sgn(fl - r) != sgn(fr - r) || sgn(fl - l) != sgn(fr - l) || sgn(fr - l) != sgn(fr - r)){
			lli m = (l + r) / 2;
			return go(d, l, m) + go(d, m+1, r);
		}else{
			return 0;
		}
	}
}

int main(){
	lli ans = 0;
	for(int d = 1; d <= 9; ++d){
		ans += go(d, 0, d*lli(1e10)-1);
	}
	cout << ans << "\n";
	return 0;
}