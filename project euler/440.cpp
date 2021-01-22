#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 987898789;

lli rec(const vector<lli> & P, const vector<lli> & init, lli n){
	int deg = P.size();
	vector<lli> ans(deg), R(2*deg);
	ans[0] = 1;
	lli p = 1;
	for(lli v = n; v >>= 1; p <<= 1);
	do{
		int d = (n & p) != 0;
		fill(R.begin(), R.end(), 0);
		for(int i = 0; i < deg; i++)
			for(int j = 0; j < deg; j++)
				(R[i + j + d] += ans[i] * ans[j]) %= mod;
		for(int i = deg-1; i >= 0; i--)
			for(int j = 0; j < deg; j++)
				(R[i + j] += R[i + deg] * P[j]) %= mod;
		copy(R.begin(), R.begin() + deg, ans.begin());
	}while(p >>= 1);
	lli nValue = 0;
	for(int i = 0; i < deg; i++)
		(nValue += ans[i] * init[i]) %= mod;
	return nValue;
}

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	int L = 2000;
	vector<int> sums(L+1);
	for(int d = 1; d <= L; ++d){
		for(int c = 1; c <= L; ++c){
			sums[d] += rec({1, 10}, {1, 10}, powerMod(c, d, mod-1));
			if(sums[d] >= mod) sums[d] -= mod;
		}
	}
	int ans = 0;
	for(int a = 1; a <= L; ++a){
		for(int b = a; b <= L; ++b){
			int d = __gcd(a, b);
			int term = 0;
			if(a/d % 2 == 1 && b/d % 2 == 1){
				term = sums[d];
			}else{
				term = 11ll * (L/2) + 10ll * (L % 2);
			}
			ans += (a == b ? 1ll : 2ll) * term % mod;
			if(ans >= mod) ans -= mod;
		}
	}
	cout << ans << "\n";
	return 0;
}

/*
T(n) = 10T(n-1) + T(n-2) , T(-1) = 0 , T(0) = 1 , T(1) = 10
ans = gcd(T(c^a), T(c^b))
U(n) = T(n-1) <--> T(n) = U(n+1)
U(n) = 10U(n-1) + U(n-2) , U(0) = 0 , U(1) = 1
U(n) is a strong divisibility sequence
ans = gcd(U(c^a + 1), U(c^b + 1)) = U(gcd(c^a + 1, c^b + 1)) = T(gcd(c^a + 1, c^b + 1) - 1)
*/