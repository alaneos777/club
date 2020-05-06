#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

map<tuple<int, vector<int>, int>, lli> mem;

lli dp(int idx, const vector<int> & freq, int sum){
	if(idx == -1){
		bool test = (sum == 0);
		for(int f : freq){
			test &= (f == 2);
		}
		return test;
	}
	auto key = make_tuple(idx, freq, sum);
	if(mem.count(key)) return mem[key];
	lli ans = 0;
	for(int d = (idx == 19 ? 1 : 0); d <= 9; ++d){
		if(freq[d] < 2){
			auto copia = freq;
			copia[d]++;
			int next = sum + ((idx & 1) ? -d : d);
			if(next < 0) next += 11;
			if(next >= 11) next -= 11;
			ans += dp(idx-1, copia, next);
		}
	}
	return mem[key] = ans;
}

int main(){
	vector<int> freq(10);
	cout << dp(19, freq, 0) << "\n";
	return 0;
}