#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 20;
vector<vector<lli>> coef(M+1);
vector<lli> den;

uint64_t mult(uint64_t a, uint64_t b, uint64_t m){
	a %= m, b %= m;
	uint64_t c = (long double)a * b / m;
	int64_t r = (int64_t)(a * b - c * m) % (int64_t)m;
	return r < 0 ? r + m : r;
}

lli SumPower(uint64_t n, int k, lli m){
	n %= m;
	uint64_t ans = 0;
	uint64_t n_pow = 1;
	for(int i = 0; i <= k+1; ++i){
		ans += mult(n_pow, (coef[k][i]%m + m)%m, m);
		if(ans >= m) ans -= m;
		n_pow = mult(n_pow, n, m);
	}
	return ans;
}

uint64_t Sigma_k(uint64_t n, int k, lli m){
	uint64_t ans = 0;
	uint64_t i = 1;
	while(i <= n){
		uint64_t ni = n / i;
		uint64_t u = n / ni;
		lli sum = SumPower(u, k, m) - SumPower(i-1, k, m);
		if(sum < 0) sum += m;
		ans += mult(sum, ni, m);
		if(ans >= m) ans -= m;
		i = u + 1;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	coef[1] = {0, 1, 1};
	coef[2] = {0, 1, 3, 2};
	coef[3] = {0, 0, 1, 2, 1};
	coef[4] = {0, -1, 0, 10, 15, 6};
	coef[5] = {0, 0, -1, 0, 5, 6, 2};
	coef[6] = {0, 1, 0, -7, 0, 21, 21, 6};
	coef[7] = {0, 0, 2, 0, -7, 0, 14, 12, 3};
	coef[8] = {0, -3, 0, 20, 0, -42, 0, 60, 45, 10};
	coef[9] = {0, 0, -3, 0, 10, 0, -14, 0, 15, 10, 2};
	coef[10] = {0, 5, 0, -33, 0, 66, 0, -66, 0, 55, 33, 6};
	den = {0, 2, 6, 4, 30, 12, 42, 24, 90, 20, 66};
	int t;
	cin >> t;
	while(t--){
		lli n, m; int k;
		cin >> n >> k >> m;
		m *= den[k];
		cout << Sigma_k(n, k, m)/den[k] << "\n";
	}
	return 0;
}