#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<bool> es_primo;
vector<lli> primos;

void criba(lli n){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	es_primo[2] = true;
	primos.push_back(2);
	for(lli i = 4; i <= n; i += 2){
		es_primo[i] = false;
	}
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					es_primo[j] = false;
				}
			}
		}
	}
}

bool primeTest(lli n){
	if(n <= 46341){
		return es_primo[n];
	}else{
		for(lli & p : primos){
			if(p * p > n) break;
			if(n % p == 0) return false;
		}
		return true;
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(46341);
	lli n;
	while(cin >> n && n != 0){
		if(primeTest(n)){
			lli b = (((lli)1) << n) - 1;
			if(primeTest(b)){
				lli ans = (((lli)1) << (n - 1)) * b;
				cout << "Perfect: " << ans << "!\n";
			}else{
				cout << "Given number is prime. But, NO perfect number is available.\n";
			}
		}else{
			cout << "Given number is NOT prime! NO perfect number is available.\n";
		}
	}
	return 0;
}