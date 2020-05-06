#include <bits/stdc++.h>
using namespace std;
using lli = __int128;

const lli N = 1e10;
const int M = pow(N, 2.0/3.0);

vector<int> mu(M+1, 1);

void sieve(){
	vector<int> cnt(M+1), acum(M+1), primes;
	vector<bool> isPrime(M+1, true);
	for(int i = 2; i <= M; ++i){
		if(isPrime[i]){ //case base: f(p)
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
				mu[d] = 0;
				cnt[d] = cnt[i] + 1;
				acum[d] = acum[i] * p;
				break;
			}else{ //gcd(i, p) = 1
				mu[d] = -mu[i];
				cnt[d] = 1;
				acum[d] = p;
			}
		}
	}
}

lli power(lli a, lli n){
	lli ans = 1;
	while(n){
		if(n & 1) ans = ans * a;
		n >>= 1;
		a = a * a;
	}
	return ans;
}

vector<lli> USmall(M+1);
unordered_map<lli, lli> UBig;

lli U(lli n){
	if(n <= M) return USmall[n];
	if(UBig.count(n)) return UBig[n];
	lli ans = 1;
	int m = sqrt(n);
	for(int k = 2, l = n/m; k <= l; ++k){
		ans -= U(n/k);
	}
	for(int k = 1; k < m; ++k){
		ans -= (n/k - n/(k+1)) * U(k);
	}
	return UBig[n] = ans;
}

lli D(lli n, int p){
	lli ans = 0;
	lli i = 1;
	while(i <= n){
		lli ni = n / i, u = n / ni;
		ans += (U(u) - U(i-1)) * power(ni, p);
		i = u + 1;
	}
	return ans;
}

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

int main(){
	sieve();
	for(int i = 1; i <= M; ++i){
		USmall[i] = USmall[i-1] + mu[i];
	}
	lli ans = D(N, 3) + 3 + 3*D(N, 2);
	cout << ans << "\n";
	return 0;
}