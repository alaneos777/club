#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

lli mem[20], ten[20];

inline pair<int, int> limits(int pos, int where, const vector<int> & digits){
	if(pos < where) return {0, 9};
	if(pos == where) return {0, digits[pos] - 1};
	return {digits[pos], digits[pos]};
}

lli dp(int pos, int where, const vector<int> & digits){
	if(pos == (digits.size()+1)/2){
		return 1;
	}
	lli & ans = mem[pos];
	if(ans != -1) return ans;
	ans = 0;
	int start, end, start_rev, end_rev;
	tie(start, end) = limits(pos, where, digits);
	if(pos == 0 && start == 0) start++;
	tie(start_rev, end_rev) = limits((int)digits.size()-1-pos, where, digits);
	for(int d = max(start, start_rev); d <= min(end, end_rev); ++d){
		ans += dp(pos + 1, where, digits);
	}
	return ans;
}

lli f(lli n){
	if(n < 0) return 0;
	if(n == 0) return 1;
	vector<int> digits;
	while(n > 0){
		digits.push_back(n % 10);
		n /= 10;
	}
	int len = digits.size();
	lli ans = (len % 2 == 1 ? 2ll * ten[(len-1)/2] : 11ll * ten[len/2-1]) - 2;
	for(int i = -1; i < (int)digits.size(); ++i){
		memset(mem, -1, sizeof(mem));
		ans += dp(0, i, digits);
	}
	return ans+1;
}

int main(){
	//ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ten[0] = 1;
	for(int i = 1; i < 20; ++i){
		ten[i] = 10ll * ten[i-1];
	}
	int t;
	cin >> t;
	for(int c = 1; c <= t; ++c){
		lli l, r;
		cin >> l >> r;
		if(l > r) swap(l, r);
		cout << "Case " << c << ": " << f(r)-f(l-1) << "\n";
	}
	return 0;
}