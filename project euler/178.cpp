#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

map<tuple<int, array<bool, 10>, int>, lli> mem;

const int M = 40;

lli f(int idx, const array<bool, 10> & appears, int last){
	if(idx == -1){
		bool t = true;
		for(int d = 0; d <= 9; ++d){
			t &= appears[d];
		}
		return t;
	}
	auto key = make_tuple(idx, appears, last);
	if(mem.count(key)) return mem[key];
	lli ans = 0;
	if(last == -1){
		for(int d = 1; d <= 9; ++d){
			auto next = appears;
			next[d] = true;
			ans += f(idx-1, next, d);
		}
	}else{
		if(0 <= last-1 && last-1 <= 9){
			auto next = appears;
			next[last-1] = true;
			ans += f(idx-1, next, last-1);
		}
		if(0 <= last+1 && last+1 <= 9){
			auto next = appears;
			next[last+1] = true;
			ans += f(idx-1, next, last+1);
		}
	}
	return mem[key] = ans;
}

int main(){
	lli ans = 0;
	for(int i = 10; i <= M; ++i){
		mem.clear();
		array<bool, 10> appears;
		for(int d = 0; d <= 9; ++d){
			appears[d] = 0;
		}
		ans += f(i-1, appears, -1);
	}
	cout << ans << "\n";
	return 0;
}