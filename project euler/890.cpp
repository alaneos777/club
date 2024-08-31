#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using lli = long long int;
using Integer = boost::multiprecision::cpp_int;

const lli mod = 1e9 + 7;

const int M = 3000;
vector<int> fact(M+1, 1), inv(M+1, 1), invfact(M+1, 1);
map<Integer, int> mem[M+1];

Integer power(Integer a, lli b){
	Integer ans = 1;
	while(b){
		if(b&1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

int ncr(int n, int r){
	if(r < 0 || r > n) return 0;
	return (lli)fact[n] * invfact[r] % mod * invfact[n-r] % mod;
}

int g(Integer n, int t){
	if(n < 0) return 0;
	if(n == 0 || t == 0) return 1;
	if(mem[t].count(n)) return mem[t][n];
	int ans = 0;
	Integer pw = Integer(1) << (t-1);
	if(n < pw*t){
		ans = g(n - pw, t) + g(n, t-1);
		if(ans >= mod) ans -= mod;
	}else{
		Integer N = n;
		for(int i = 1; i <= t+1; ++i){
			N -= pw;
			int r = (lli)g(N, t) * ncr(t+1, i) % mod;
			if(i&1){
				ans += r;
				if(ans >= mod) ans -= mod;
			}else{
				ans -= r;
				if(ans < 0) ans += mod;
			}
		}
	}
	return mem[t][n] = ans;
}

int p(Integer n){
	n >>= 1;
	Integer tmp = n;
	int t = 0;
	while(tmp > 0){
		t++;
		tmp >>= 1;
	}
	return g(n, t);
}

int main(){
	for(lli i = 2; i <= M; ++i){
		fact[i] = i * fact[i-1] % mod;
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
		invfact[i] = (lli)inv[i] * invfact[i-1] % mod;
	}
	Integer N = power(7, 777);
	cout << p(N) << "\n";
	return 0;
}