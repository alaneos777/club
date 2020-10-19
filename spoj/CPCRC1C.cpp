#include <bits/stdc++.h>
using namespace std;
using lli = int64_t;

lli mem[15][2][100];

lli f(int pos, bool canUseAll, int sum, const vector<int> & digits){
	if(pos == digits.size()) return sum;
	lli & ans = mem[pos][canUseAll][sum];
	if(ans != -1) return ans;
	ans = 0;
	int limit = canUseAll ? 9 : digits[pos];
	for(int d = 0; d <= limit; ++d){
		ans += f(pos + 1, canUseAll | d < limit, sum + d, digits);
	}
	return ans;
}

lli f(int n){
	if(n <= 0) return 0;
	vector<int> digits;
	while(n){
		digits.push_back(n % 10);
		n /= 10;
	}
	reverse(digits.begin(), digits.end());
	memset(mem, -1, sizeof(mem));
	return f(0, false, 0, digits);
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int a, b;
	while(cin >> a >> b){
		if(a == -1 && b == -1) break;
		cout << f(b) - f(a-1) << "\n";
	}
	return 0;
}