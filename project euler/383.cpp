#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int digit_sum(int n){
	int ans = 0;
	while(n){
		ans += n % 5;
		n /= 5;
	}
	return ans;
}

lli N = 1e18;
vector<int> digits;

map<tuple<int, int, int, int>, lli> mem;

lli dp(int idx, int sum, int sum2, int carry, bool f, int zeros, int pos){
	if(idx == digits.size()){
		return sum <= sum2 + digit_sum(carry) - 1 + 4*zeros;
	}
	auto tup = make_tuple(idx, sum - sum2, carry, zeros);
	if(mem.count(tup)) return mem[tup];
	lli & ans = mem[tup];
	ans = 0;
	int l, r;
	if(idx < pos){
		l = 0, r = 4;
	}else if(idx == pos){
		l = 0, r = digits[idx] - 1;
	}else{
		l = r = digits[idx];
	}
	for(int d = l; d <= r; ++d){
		ans += dp(idx + 1, sum + 2*d, sum2 + (carry + 2*d)%5, (carry + 2*d)/5, f & (d == 0), (f & (d == 0)) ? zeros + 1 : zeros, pos);
	}
	return ans;
}

int main(){
	while(N){
		digits.push_back(N % 5);
		N /= 5;
	}
	lli ans = 0;
	for(int i = 0; i < digits.size(); ++i){
		mem.clear();
		ans += dp(0, 0, 0, 0, true, 0, i);
	}
	cout << ans << "\n";
	return 0;
}