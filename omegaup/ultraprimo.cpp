#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<bool> sieve(int n){
	vector<int> primes;
	vector<bool> isPrime(n+1, true);
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
	isPrime[0] = false;
	isPrime[1] = false;
	return isPrime;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<bool> isPrime = sieve(1000);
	int m;
	cin >>m;
	while(m--){
		string str;
		cin >> str;
		int s = 0;
		for(char c : str) if('0'<=c && c<='9') s += (c-'0');
		if(!isPrime[s]) cout << "No ";
		cout << "UltraPrimo\n";
	}
	return 0;
}