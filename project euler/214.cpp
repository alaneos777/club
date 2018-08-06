#include <bits/stdc++.h>
using namespace std;

vector<int> lowestPrime;
void criba(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; i ++) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2){
		if(lowestPrime[i] == i){
			for(int j = i * i; j <= n; j += 2 * i){
				if(lowestPrime[j] == j) lowestPrime[j] = i;
			}
		}
	}
}

int phi(int n){
	int ans = n;
	while(n != 1){
		int p = lowestPrime[n];
		while(n % p == 0) n /= p;
		ans -= ans / p;
	}
	return ans;
}

vector<int> chain;

int calc(int n){
	int n0 = n;
	int ans = 0;
	while(n != 1){
		if(chain[n] > 0){
			ans += chain[n];
			break;
		}else{
			n = phi(n);
			ans++;
		}
	}
	chain[n0] = ans;
	return ans;
}

int main(){
	clock_t begin = clock();
	int n = 40000000;
	long long int sum = 0;
	criba(n);
	chain.resize(n + 1, 0);
	for(int i = 1; i <= n; i++){
		if(lowestPrime[i] == i && calc(i) == 24){
			sum += i;
		}
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << sum << "\n";
	cout << fixed << setprecision(4) << elapsed_secs << "s";
}