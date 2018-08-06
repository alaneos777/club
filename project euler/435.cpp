#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef vector<vector<lli>> matrix;

matrix mult(matrix & A, matrix & B, lli mod){
	int m = A.size(), n = B.size(), p = B[0].size();
	matrix C(m, vector<lli>(n));
	for(int i = 0; i < m; i++){
		for(int j = 0; j < p; j++){
			for(int k = 0; k < n; k++){
				C[i][j] = ((A[i][k] * B[k][j]) % mod + C[i][j]) % mod;
			}
		}
	}
	return C;
}

pair<lli, lli> inv(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1 != 0){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	return {r0, s0};
}

lli exp(lli a, lli b, lli mod){
	a %= mod;
	lli ans = 1;
	while(b){
		if(b & 1) ans = (ans * a) % mod;
		b >>= 1;
		a = (a * a) % mod;
	}
	return ans;
}

vector<lli> f(lli n, lli mod){
	matrix A = {{1, 1}, {1, 0}};
	matrix ans = {{1, 0}, {0, 1}};
	while(n){
		if(n & 1) ans = mult(ans, A, mod);
		n >>= 1;
		if(n) A = mult(A, A, mod);
	}
	return {ans[1][0], ans[0][0]};
}

lli F(lli n, lli x, lli mod, lli fn, lli fn_1){
	lli den = x * (x + 1) - 1;
	pair<lli, lli> info = inv(den, mod);
	if(info.first == 1){
		lli xn = exp(x, n, mod);
		lli num = (x * fn) % mod;
		num = (num + fn_1) % mod;
		num = (num * xn - 1) % mod;
		num = (num * x) % mod;
		num = (num * info.second) % mod;
		if(num < 0) num += mod;
		return num;
	}else{
		mod *= den;
		lli xn = exp(x, n, mod);
		vector<lli> fib = f(n, mod);
		lli num = (x * fib[0]) % mod;
		num = (num + fib[1]) % mod;
		num = (num * xn - 1) % mod;
		num = (num * x) % mod;
		num /= den;
		return num;
	}
}

lli sum(lli n, lli x, lli mod){
	lli ans = 0;
	vector<lli> fib = f(n, mod);
	for(lli i = 1; i <= x; i++){
		lli tmp = F(n, i, mod, fib[0], fib[1]);
		ans = (ans + tmp) % mod;
	}
	return ans;
}

int main(){
	clock_t begin = clock();
	lli n = 1e15, x = 100;
	//vector<lli> factors = {2048, 729, 125, 49, 11, 13};
	vector<lli> factors = {1492992, 6125, 143};
	lli factorial = 1307674368000;
	lli ans = 0;
	for(lli & mod : factors){
		lli ai = sum(n, x, mod);
		lli P = factorial / mod;
		lli tmp = (ai * P) % factorial;
		tmp = (tmp * inv(P, mod).second) % factorial;
		ans = (ans + tmp) % factorial;
	}
	if(ans < 0) ans += factorial;
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << ans << "\n";
	cout << fixed << setprecision(4) << elapsed_secs << "s";
	return 0;
}