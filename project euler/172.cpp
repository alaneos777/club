#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

map<tuple<int, array<uint8_t, 10>>, lli> mem;

const int M = 18;

lli f(int idx, const array<uint8_t, 10> & freq){
	if(idx == -1){
		return 1;
	}
	auto key = make_tuple(idx, freq);
	if(mem.count(key)) return mem[key];
	lli ans = 0;
	for(int d = 0; d <= 9; ++d){
		if(d == 0 && idx == M-1) continue;
		if(freq[d] == 3) continue;
		auto next = freq;
		next[d]++;
		ans += f(idx-1, next);
	}
	return mem[key] = ans;
}

int main(){
	array<uint8_t, 10> freq;
	for(int d = 0; d <= 9; ++d){
		freq[d] = 0;
	}
	cout << f(M-1, freq) << "\n";
	return 0;
}