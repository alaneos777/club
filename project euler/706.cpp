#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int M = 1e5;

map<tuple<int, array<uint8_t, 3>, uint8_t>, int> mem;

int f(int idx, const array<uint8_t, 3> & cnt, uint8_t sum){
	if(idx == -1){
		return (sum == 0);
	}
	auto key = make_tuple(idx, cnt, sum);
	if(mem.count(key)) return mem[key];
	int ans = 0;
	for(uint8_t d = 0; d <= 9; ++d){
		if(d == 0 && idx == M-1) continue;
		array<uint8_t, 3> cp;
		cp[d%3] = (cnt[0] + 1) % 3;
		cp[(d+1)%3] = cnt[1];
		cp[(d+2)%3] = cnt[2];
		uint8_t n_sum = (sum + cp[0]) % 3;
		ans += f(idx-1, cp, n_sum);
		if(ans >= mod) ans -= mod;
	}
	return mem[key] = ans;
}

int main(){
	array<uint8_t, 3> cnt;
	for(int d = 0; d < 3; ++d){
		cnt[d] = 0;
	}
	cout << f(M-1, cnt, 0) << "\n";
	return 0;
}