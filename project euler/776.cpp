#include <bits/stdc++.h>
using namespace std;
using lli = __int128_t;
using ld = long double;

const vector<int> digits = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
const int LEN = digits.size();

lli mem_f[20][200][2][200];
lli mem_g[20][200][2][200];
vector<lli> ten(LEN+1);

lli f(int pos, int sum, bool canUseAll, int target){
	if(pos == LEN) return sum == target;
	lli& ans = mem_f[pos][sum][canUseAll][target];
	if(ans != -1) return ans;
	ans = 0;
	int limit = canUseAll ? 9 : digits[pos];
	for(int d = 0; d <= limit; ++d){
		if(sum + d > target) break;
		ans += f(pos+1, sum+d, canUseAll | (d < digits[pos]), target);
	}
	return ans;
}

lli g(int pos, int sum, bool canUseAll, int target){
	if(pos == LEN) return 0;
	lli& ans = mem_g[pos][sum][canUseAll][target];
	if(ans != -1) return ans;
	ans = 0;
	int limit = canUseAll ? 9 : digits[pos];
	for(int d = 0; d <= limit; ++d){
		if(sum + d > target) break;
		ans += d*ten[LEN-1-pos]*f(pos+1, sum+d, canUseAll | (d < digits[pos]), target) + g(pos+1, sum+d, canUseAll | (d < digits[pos]), target);
	}
	return ans;
}

int main(){
	memset(mem_f, -1, sizeof(mem_f));
	memset(mem_g, -1, sizeof(mem_g));
	ten[0] = 1;
	for(int i = 1; i <= LEN; ++i){
		ten[i] = 10 * ten[i-1];
	}

	ld ans = 0;
	for(int i = 1; i <= 9*LEN; ++i){
		ans += g(0, 0, false, i) / ld(i);
	}

	int digits = (int)log10l(ans);
	cout << fixed << setprecision(12) << ans/powl(10, digits) << "e" << digits << "\n";
	
	return 0;
}