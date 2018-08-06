#include <bits/stdc++.h>
using namespace std;

vector<int> primos;

void criba(int n){
	primos.push_back(2);
	vector<bool> es_primo(n + 1, true);
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

void factorizar(int n, map<int, int> & f){
	for(int & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			int pot = 0;
			while(n % p == 0){
				n /= p;
				++pot;
			}
			f[p] += pot;
		}
	}
	if(n > 1){
		f[n]++;
	}
}

void factorizacion(map<int, int> & a, map<int, int> & b, map<int, int> & c){
	for(pair<const int, int> & x : a){
		int pot = x.second - b[x.first] - c[x.first];
		if(pot >= 1){
			cout << x.first;
			if(pot > 1){
				cout << "^" << pot;
			}
			cout << "x";
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int t, n;
	cin >> t;
	criba(32);
	vector< map<int, int> > factorizaciones(1001);
	for(int i = 2; i <= 1000; ++i){
		factorizaciones[i] = factorizaciones[i - 1];
		factorizar(i, factorizaciones[i]);
	}
	while(t--){
		cin >> n;
		if(n == 0){
			cout << "1\n";
			continue;
		}
		cout << "A";
		if(n > 1)
			cout << "^" << n;
		cout << "+";
		for(int i = 1; i < n; ++i){
			factorizacion(factorizaciones[n], factorizaciones[i], factorizaciones[n - i]);
			cout << "A";
			if(n - i > 1)
				cout << "^" << (n - i);
			cout << "B";
			if(i > 1)
				cout << "^" << i;
			cout << "+";
		}
		cout << "B";
		if(n > 1)
			cout << "^" << n;
		cout << "\n";
	}
	return 0;
}