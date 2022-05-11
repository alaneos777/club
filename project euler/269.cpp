#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

const int M = 16;

lli mem_f[M][80];
lli mem_g[M][80][80];
lli mem_h[M][80][80][80];
const int off = 39;

lli f(int a, int pos = M-1, int s = 0){
	if(pos == -1) return s == 0;
	lli& ans = mem_f[pos][s+off];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(d == 0 && pos == 0) continue;
		int nxt_s = d - a*s;
		if(abs(nxt_s) <= off){
			ans += f(a, pos-1, nxt_s);
		}
	}
	return ans;
}

lli g(int a, int b, int pos = M-1, int s = 0, int t = 0){
	if(pos == -1) return s == 0 && t == 0;
	lli& ans = mem_g[pos][s+off][t+off];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(d == 0 && pos == 0) continue;
		int nxt_s = d - a*s;
		int nxt_t = d - b*t;
		if(abs(nxt_s) <= off && abs(nxt_t) <= off){
			ans += g(a, b, pos-1, nxt_s, nxt_t);
		}
	}
	return ans;
}

lli h(int a, int b, int c, int pos = M-1, int s = 0, int t = 0, int u = 0){
	if(pos == -1) return s == 0 && t == 0 && u == 0;
	lli& ans = mem_h[pos][s+off][t+off][u+off];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(d == 0 && pos == 0) continue;
		int nxt_s = d - a*s;
		int nxt_t = d - b*t;
		int nxt_u = d - c*u;
		if(abs(nxt_s) <= off && abs(nxt_t) <= off && abs(nxt_u) <= off){
			ans += h(a, b, c, pos-1, nxt_s, nxt_t, nxt_u);
		}
	}
	return ans;
}

int main(){
	lli ans = powl(10, M-1);
	for(int a = 1; a <= 9; ++a){
		memset(mem_f, -1, sizeof(mem_f));
		ans += f(a);
	}
	for(int a = 1; a <= 9; ++a){
		for(int b = a+1; b <= 9; ++b){
			if(a*b >= 10) break;
			memset(mem_g, -1, sizeof(mem_g));
			ans -= g(a, b);
		}
	}
	memset(mem_h, -1, sizeof(mem_h));
	ans += h(1, 2, 3);
	memset(mem_h, -1, sizeof(mem_h));
	ans += h(1, 2, 4);
	cout << ans << "\n";
	return 0;
}