#include <bits/stdc++.h>
using namespace std;
typedef __int128 lli;

lli mod = 1e9;
lli mod2 = 6e9;

lli sum_2(lli n){
	lli ans = n * (n + 1) % mod2 * (2 * n + 1) % mod2 / 6;
	return ans % mod;
}

int main(){
	clock_t begin = clock();
	lli n = 1e15;
	lli ans = 0;
	lli m = sqrt(n);
	lli limit = n / m;
	for(lli k = 1; k <= limit; ++k){
		ans += k * k * (n / k);
	}
	for(lli k = 1; k < m; ++k){
		ans += (sum_2(n / k) - sum_2(n / (k + 1))) * k;
	}
	ans %= mod;
	if(ans < 0) ans += mod;
	long long ans_ = ans;
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << ans_ << "\n";
	cout << fixed << setprecision(4) << elapsed_secs << "s\n";
	return 0;
}