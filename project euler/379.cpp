#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli N = 1e12;
const int M = pow(N, 2.0/3.0);

vector<int> divs(M+1, 1), mu(M+1, 1);

void sieve(){
	vector<int> cnt(M+1), acum(M+1), primes;
	vector<bool> isPrime(M+1, true);
	for(int i = 2; i <= M; ++i){
		if(isPrime[i]){ //case base: f(p)
			divs[i] = 2;
			mu[i] = -1;
			primes.push_back(i);
			cnt[i] = 1;
			acum[i] = i;
		}
		for(int p : primes){
			int d = i * p;
			if(d > M) break;
			isPrime[d] = false;
			if(i % p == 0){ //gcd(i, p) != 1
				divs[d] = divs[i / acum[i]] * (cnt[i] + 2);
				mu[d] = 0;
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				divs[d] = divs[i] * 2;
				mu[d] = -mu[i];
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
}

vector<lli> HSmall(M+1), USmall(M+1);

lli H(lli n){
	if(n <= M) return HSmall[n];
	lli ans = 0;
	lli i = 1;
	while(i <= n){
		lli ni = n / i;
		lli u = n / ni;
		ans += (u - (i-1)) * ni;
		i = u + 1;
	}
	return ans;
}

lli U(lli n){
	if(n <= M) return USmall[n];
	lli ans = 0;
	for(lli k = 1; k*k <= n; ++k){
		ans += mu[k] * (n / (k*k));
	}
	return ans;
}

lli F(lli n){
	lli ans = 0;
	lli m = sqrt(n);
	for(lli k = 1, lim = n/m; k <= lim; ++k){
		ans += U(n/k) * divs[k];
	}
	for(lli k = 1; k <= m-1; ++k){
		ans += (H(n/k) - H(n/(k+1))) * U(k);
	}
	return ans;
}

int main(){
	sieve();
	for(int i = 1; i <= M; ++i){
		HSmall[i] = HSmall[i-1] + divs[i];
		USmall[i] = USmall[i-1] + mu[i]*mu[i];
	}
	cout << (F(N) + N) / 2 << "\n";
	return 0;
}