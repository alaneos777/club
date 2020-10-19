#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

lli mem[17][2][150];

lli dp(int pos, bool canUseAll, int sum, const vector<int> & digits_n){
	if(pos == digits_n.size()){
		return sum;
	}
	lli & ans = mem[pos][canUseAll][sum];
	if(ans != -1) return ans;
	ans = 0;
	int limit = canUseAll ? 9 : digits_n[pos];
	for(int d = 0; d <= limit; ++d){
		ans += dp(pos + 1, canUseAll | d < limit, sum + d, digits_n);
	}
	return ans;
}

lli f(lli n){
	if(n <= 0) return 0;
	vector<int> digits_n;
	while(n > 0){
		digits_n.push_back(n % 10);
		n /= 10;
	}
	reverse(digits_n.begin(), digits_n.end());
	memset(mem, -1, sizeof(mem));
	return dp(0, false, 0, digits_n);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t--){
		lli a, b;
		cin >> a >> b;
		lli ans = f(b) - f(a-1);
		cout << ans << "\n";
	}
	return 0;
}