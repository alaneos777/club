#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using lli = long long int;

auto eulerianNumbers(lli n){
	vector<vector<lli>> euler(n+1, vector<lli>(n+1));
	for(int i = 1; i <= n; ++i){
		euler[i][0] = 1;
		for(int j = 1; j < i; ++j){
			euler[i][j] = (i-j) * euler[i-1][j-1] + (j+1) * euler[i-1][j];
		}
	}
	return euler;
}

const int k = 15;
const auto euler = eulerianNumbers(k);

ld g(ld r){
	ld ans = 0;
	ld r_pow = r;
	for(int i = 0; i <= k-1; ++i){
		ans += euler[k][i] * r_pow;
		r_pow *= r;
	}
	ans /= powl(1 - r, k+1);
	return ans;
}

int main(){
	ld ans = 0;
	// converges very fast
	ld x = 1 - 1.0l / (1 << 25);
	ld r = x;
	for(int j = 1; j <= 10; ++j){
		ans += g(r);
		r *= x;
	}
	int pot_10 = log10l(ans);
	ans /= powl(10, pot_10);
	cout << fixed << setprecision(12) << ans;
	cout << "e" << pot_10 << "\n";

	// does not converge fast
	/*ans = 0;
	for(int n = 1; n <= 1000000; ++n){
		ans += powl(n, k) * (powl(x, n) / (1 - powl(x, n)));
	}
	pot_10 = log10l(ans);
	ans /= powl(10, pot_10);
	cout << fixed << setprecision(12) << ans;
	cout << "e" << pot_10 << "\n";*/
	
	return 0;
}