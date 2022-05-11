#include <bits/stdc++.h>
using namespace std;
using lli = uint64_t;
using tup = array<int, 9>;

const int M = 16;

int low[10] = {0, 0, -3, -1, 0, 0, 0, 0, 0, 0};
int upp[10] = {0, 0, 6, 3, 2, 1, 1, 1, 1, 1};

lli power(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

map<tup, lli> mem[M];
lli f(int pos, tup res){
	if(pos == -1){
		for(int i = 1; i <= 9; ++i){
			if(res[i-1] == 0) return 1;
		}
		return 0;
	}
	if(mem[pos].count(res)) return mem[pos][res];
	lli ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(pos == 0 && d == 0) continue;
		tup nxt_res;
		for(int a = 1; a <= 9; ++a){
			nxt_res[a-1] = d - res[a-1]*a;
			if(a > 1 && (nxt_res[a-1] > upp[a] || nxt_res[a-1] < low[a])) nxt_res[a-1] = 999;
		}
		ans += f(pos-1, nxt_res);
	}
	return mem[pos][res] = ans;
}

int main(){
	lli ans = power(10, M-1) + f(M-1, tup());
	cout << ans << "\n";
	return 0;
}