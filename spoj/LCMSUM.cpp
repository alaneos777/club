#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> primos;

void criba(lli n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
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

lli lcmsum(lli n){
	lli ans = 1, k = n;
	for(lli & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			lli num = 1;
			while(n % p == 0){
				n /= p;
				num *= p;
			}
			num = num * num * p + 1;
			lli den = p + 1;
			ans *= num / den;
		}
	}
	if(n > 1) ans *= (n * n * n + 1) / (n + 1);
	return (1 + ans) * k / 2;
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(1000);
	int t;
	cin >> t;
	while(t--){
		lli n;
		cin >> n;
		cout << lcmsum(n) << "\n";
	}
	return 0;
}