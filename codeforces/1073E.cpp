#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;
const lli mod = 998244353;

lli mem_count[20][1024][2][2];
lli mem_sum[20][1024][2][2];
lli ten[21];

lli dp_count(int pos, int mask, bool canUseAll, bool hasPrefixOfZeros, int k, const vector<int> & digits){
	if(pos == digits.size()){
		return __builtin_popcount(mask) <= k;
	}
	int limit = canUseAll ? 9 : digits[pos];
	lli & ans = mem_count[pos][mask][canUseAll][hasPrefixOfZeros];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= limit; ++d){
		if(d == 0){
			if(!hasPrefixOfZeros){
				ans += dp_count(pos+1, mask | (1 << d), canUseAll | (d < limit), false, k, digits);
			}else{
				ans += dp_count(pos+1, mask, canUseAll | (d < limit), true, k, digits);
			}
		}else{
			ans += dp_count(pos+1, mask | (1 << d), canUseAll | (d < limit), false, k, digits);
		}
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

//x = 5132 = 5*10^3 + 1*10^2 + 3*10^1 + 2*10^0
lli dp_sum(int pos, int mask, bool canUseAll, bool hasPrefixOfZeros, int k, const vector<int> & digits){
	if(pos == digits.size()){
		return 0;
	}
	int limit = canUseAll ? 9 : digits[pos];
	lli & ans = mem_sum[pos][mask][canUseAll][hasPrefixOfZeros];
	if(ans != -1) return ans;
	ans = 0;
	for(int d = 0; d <= limit; ++d){
		if(d == 0){
			if(!hasPrefixOfZeros){
				ans += (d * ten[digits.size()-1-pos] % mod * dp_count(pos+1, mask | (1 << d), canUseAll | (d < limit), false, k, digits) % mod + dp_sum(pos+1, mask | (1 << d), canUseAll | (d < limit), false, k, digits)) % mod;
			}else{
				ans += (d * ten[digits.size()-1-pos] % mod * dp_count(pos+1, mask, canUseAll | (d < limit), true, k, digits) % mod + dp_sum(pos+1, mask, canUseAll | (d < limit), true, k, digits)) % mod;
			}
		}else{
			ans += (d * ten[digits.size()-1-pos] % mod * dp_count(pos+1, mask | (1 << d), canUseAll | (d < limit), false, k, digits) % mod + dp_sum(pos+1, mask | (1 << d), canUseAll | (d < limit), false, k, digits)) % mod;
		}
		if(ans >= mod) ans -= mod;
	}
	return ans;
}

lli f(lli n, int k){
	if(n == 0) return 0;
	vector<int> digits;
	while(n > 0){
		digits.push_back(n % 10);
		n /= 10;
	}
	reverse(digits.begin(), digits.end());
	memset(mem_count, -1, sizeof(mem_count));
	memset(mem_sum, -1, sizeof(mem_sum));
	return dp_sum(0, 0, false, true, k, digits);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ten[0] = 1;
	for(int i = 1; i <= 20; ++i){
		ten[i] = 10ll * ten[i-1] % mod;
	}
	lli l, r;
	int k;
	cin >> l >> r >> k;
	lli ans = f(r, k) - f(l-1, k);
	if(ans < 0) ans += mod;
	cout << ans << "\n";
	return 0;
}