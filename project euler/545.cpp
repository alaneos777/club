#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

vector<bool> is;
vector<int> primes;
void sieve(int n){
	is.resize(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
}

lli powerMod(lli a, lli b, lli m){
	lli ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans % m;
}

bool isPrimeMillerRabin(lli n){
	if(n < 2) return false;
	if(!(n & 1)) return n == 2;
	lli d = n - 1, s = 0;
	for(; !(d & 1); d >>= 1, ++s);
	for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
		if(n == a) return true;
		lli m = powerMod(a, d, n);
		if(m == 1 || m == n - 1) continue;
		int k = 0;
		for(; k < s; ++k){
			m = m * m % n;
			if(m == n - 1) break;
		}
		if(k == s) return false;
	}
	return true;
}

const int M = 1e7;

bool test(int p){
	vector<int> candidates = {2*p+1, 4*p+1, 14*p+1, 22*p+1, 28*p+1, 44*p+1, 154*p+1, 308*p+1};
	for(int c : candidates){
		if(c <= M && is[c]) return false;
		else if(c > M && isPrimeMillerRabin(c)) return false;
	}
	return true;
}

int main(){
	sieve(M);
	vector<int> a = {1}, b, mult;
	for(int p : primes){
		if(p == 2 || p == 3 || p == 5 || p == 23 || p == 29) continue;
		if(test(p)){
			a.push_back(p);
			if(a.size() == 100000) break;
		}
	}
	int last = a.back();
	for(int i = 1; i < a.size(); ++i){
		int p = a[i];
		if(p*p > last) break;
		if(test(p*p)){
			b.push_back(p*p);
		}
	}
	for(int i = 1; i < a.size()-1; ++i){
		int p = a[i];
		for(int j = i+1; j < a.size(); ++j){
			int q = a[j];
			if((lli)p*q > last) break;
			if(test(p*q)){
				b.push_back(p*q);
			} 
		}
	}
	for(int i = 1; i < a.size()-1; ++i){
		int p = a[i];
		if((lli)p*p > last) break;
		for(int j = i+1; j < a.size(); ++j){
			int q = a[j];
			if((lli)p*p*q > last) break;
			if(test(p*p*q) && test(p*p) && test(p*q)){
				b.push_back(p*p*q);
			}
		}
	}
	sort(b.begin(), b.end());
	merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(mult));
	cout << mult[100000-1]*308 << "\n";
	return 0;
}