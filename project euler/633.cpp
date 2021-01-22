// https://arxiv.org/pdf/1604.05671.pdf
#include <bits/stdc++.h>
using namespace std;

auto sieve(int n){
	vector<int> primes, lp(n+1);
	for(int i = 2; i <= n; ++i){
		if(lp[i] == 0){
			primes.push_back(i);
			lp[i] = i;
		}
		for(int p : primes){
			int d = i*p;
			if(d > n) break;
			lp[d] = p;
			if(lp[i] == p) break;
		}
	}
	return primes;
}

const auto primes = sieve(2e6);
const double pi = acos(-1);

int main(){
	int k = 7;
	vector<double> P(k+1), S(k+1);
	for(int i = 1; i <= k; ++i){
		for(int p : primes){
			P[i] += pow(1.0 / (1.0 - 1.0*p*p), i);
		}
	}
	for(int i = 1; i <= k; ++i){
		S[i] = P[i];
		int sgn = -1;
		for(int j = 1; j < i; ++j){
			S[i] += sgn*S[j]*P[i-j];
			sgn = -sgn;
		}
		S[i] *= -sgn;
		S[i] /= i;
	}
	double ans = S[k] * 6.0/(pi*pi);
	if(k & 1) ans = -ans;
	int lg = -(int)ceil(-log10(ans));
	cout << fixed << setprecision(4) << ans*pow(10, -lg);
	cout << "e" << lg << "\n";
	return 0;
}