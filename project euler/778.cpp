#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const lli mod = 1e9 + 9;

using poly = vector<lli>;

poly operator*(const poly& a, const poly& b){
	poly c(10);
	for(int i = 0; i < a.size(); ++i){
		for(int j = 0; j < b.size(); ++j){
			(c[i*j%10] += a[i]*b[j]) %= mod;
		}
	}
	return c;
}

poly power(poly a, lli n){
	poly ans = {0, 1};
	while(n){
		if(n & 1) ans = ans * a;
		n >>= 1;
		a = a * a;
	}
	return ans;
}

int main(){
	int r = 234567, m = 765432;
	int digits = log10l(m) + 1;
	vector<poly> freq(digits, poly(10));
	for(int n = 0; n <= m; ++n){
		int k = n, pos = 0;
		do{
			freq[pos++][k%10]++;
			k /= 10;
		}while(k);
	}
	lli ans = 0, ten = 1;
	for(int pos = 0; pos < digits; ++pos){
		poly col = power(freq[pos], r);
		lli term = 0;
		for(int d = 0; d < col.size(); ++d){
			(term += d*col[d]) %= mod;
		}
		(ans += term * ten) %= mod;
		ten = ten * 10 % mod;
	}
	cout << ans << "\n";
	return 0;
}