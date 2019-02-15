#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<int> primes;
vector<bool> isPrime;

void sieve(int n){
	isPrime.resize(n+1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= n; ++i){
		if(isPrime[i])
			primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			isPrime[d] = false;
			if(i % p == 0) break;
		}
	}
}

using Long = __int128;
Long powerMod(Long a, Long b, Long m){
	Long ans = 1;
	a %= m;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

bool miller_rabin(Long n){
	if(n < 2) return false;
	if(n == 2) return true;
	Long d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int i = 0; i < 16; ++i){
		Long a = 1 + rand() % (n - 1);
		Long m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) goto exit;
		for(int k = 0; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) goto exit;
		}
		return false;
		exit:;
	}
	return true;
}

bool prime(lli n){
	if(n < isPrime.size()) return isPrime[n];
	else return miller_rabin(n);
}

bool check(const vector<lli> & conj){
	if(conj.size() == 1) return prime(conj[0]);
	for(int i = 0; i < conj.size(); ++i){
		for(int j = i+1; j < conj.size(); ++j){
			lli m = stoll(to_string(conj[i]) + to_string(conj[j]));
			lli n = stoll(to_string(conj[j]) + to_string(conj[i]));
			if(!(prime(m) && prime(n))) return false;
		}
	}
	return true;
}

void go(int pos, int last, vector<lli> conj){
	if(!check(conj)) return;
	if(pos == 5){
		lli sum = 0;
		for(lli p : conj){
			sum += p;
			cout << p << " ";
		}
		cout << "\n" << sum << "\n";
		exit(0);
	}else{
		for(int i = last; i < primes.size(); ++i){
			int pi = primes[i];
			auto conj2 = conj;
			conj2.push_back(pi);
			go(pos + 1, i+1, conj2);
		}
	}
}

int main(){
	srand(time(0));
	sieve(10000);
	primes.erase(primes.begin());
	primes.erase(primes.begin()+1);
	go(0, 0, {});
	return 0;
}