#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> primos;

lli mod(lli a, lli b){
	lli r = a % b;
	if(r < 0) r += b;
	return r;
}

lli inv(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1 != 0){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

void criba(lli n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2*i){
					es_primo[j] = false;
				}
			}
		}
	}
}

lli mult_bin_mod(lli a, lli b, lli n){
	lli ans = 0;
	a %= n, b %= n;
	if(abs(b) > abs(a)) swap(a, b);
	if(b < 0){
		a *= -1, b *= -1;
	}
	while(b){
		if(b & 1) ans = (ans + a) % n;
		b >>= 1;
		a = (a + a) % n;
	}
	return ans;
}

lli S(lli p){
	lli ans = 1;
	for(lli k = 4; k >= 1; k--){
		ans = mod(mult_bin_mod(ans, inv(p - k, p), p) + 1, p);
	}
	return mod(-ans, p);
}

int main(){
	criba(100000000);
	cout << "hola\n";
	lli sum = 0;
	lli n;
	cin >> n;
	for(lli & p : primos){
		if(5 <= p && p < n){
			sum += S(p);
		}
	}
	cout << sum << "\n";
	return 0;
}