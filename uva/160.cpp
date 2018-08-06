#include <bits/stdc++.h>
using namespace std;

void criba_primos(int n, vector<int> & primos){
	vector<bool> es_primo(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	for(int i = 4; i <= n; i += 2)
		es_primo[i] = false;
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(es_primo[i])
			for(int j = i * i; j <= n; j += 2 * i)
				es_primo[j] = false;
	primos.push_back(2);
	for(int i = 3; i <= n; i += 2)
		if(es_primo[i])
			primos.push_back(i);
}

int potencia(int n, int p){
	int ans = 0, pot = p;
	while(pot <= n){
		ans += n / pot;
		pot *= p;
	}
	return ans;
}

int factorizar_factorial(int n, vector<int> & primos, vector<int> & f){
	int i = 0, p;
	for(i = 0; i < primos.size(); ++i){
		p = primos[i];
		if(p > n) break;
		f[i] = potencia(n, p);
	}
	return i - 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<int> primos;
	criba_primos(100, primos);
	int n;
	while(true){
		cin >> n;
		if(n == 0) break;
		vector<int> f(primos.size(), 0);
		int limit = factorizar_factorial(n, primos, f);
		cout << setw(3) << n;
		cout << "! =";
		for(int i = 0; i <= limit; i++){
			if(i > 0 && i % 15 == 0){
				cout << "\n      ";
			}
			cout << setw(3) << f[i];
		}
		cout << "\n";
	}
	return 0;
}