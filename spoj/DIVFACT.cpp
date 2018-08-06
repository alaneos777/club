#include <bits/stdc++.h>
using namespace std;

vector<int> primos;
vector<bool> es_primo;
int m = 1000000007;

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

int pot(int n, int p){
	int prod = p;
	int ans = 0;
	while(prod <= n){
		ans += n / prod;
		prod *= p;
	}
	return ans;
}

long long int divisors(int n){
	long long int ans = 1;
	for(int & p : primos){
		if(p > n) break;
		ans = (ans * (pot(n, p) + 1)) % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(50000);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		cout << divisors(n) << "\n";
	}
	return 0;
}