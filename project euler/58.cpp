#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<bool> es_primo;
vector<int> primos;

void criba(int n){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	primos.push_back(2);
	for(int i = 4; i <= n; i += 2) es_primo[i] = false;
	int limit = sqrt(n);
	for(int i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(int j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

int NMAX = 1e6;

bool isPrime(lli n){
	if(n <= NMAX){
		return es_primo[n];
	}else{
		for(int & p : primos){
			if((lli)p * p > n) break;
			if(n % p == 0) return false;
		}
		return true;
	}
}

int main(){
	clock_t begin = clock();
	criba(NMAX);
	int count = 0, total = 0, n = 1;
	while(true){
		n += 2;
		total = 2 * n - 1;
		if(isPrime(n*(n-2)+2)) count++;
		if(isPrime(n*(n-3)+3)) count++;
		if(isPrime(n*(n-1)+1)) count++;
		if(10 * count < total) break;
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << n << "\n";
	cout << fixed << setprecision(4) << elapsed_secs << "s";
	return 0;
}