#include <bits/stdc++.h>
using namespace std;

vector<int> primos;

void criba(int n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
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

void factorizar(int n, map<int, int> & f, int & distinct){
	for(int & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			int pot = 0;
			while(n % p == 0){
				n /= p;
				pot++;
			}
			if(f.count(p) == 0){
				f[p] = pot;
				distinct++;
			}else{
				f[p] = abs(f[p] - pot);
			}
		}
	}
	if(n > 1){
		if(f.count(n) == 0){
			f[n] = 1;
			distinct++;
		}else{
			f[n] = abs(f[n] - 1);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(1000);
	int a, b, caso = 1;
	while(cin >> a >> b && !(a == 0 && b == 0)){
		map<int, int> f;
		int distinct = 0, distance = 0;
		factorizar(a, f, distinct);
		factorizar(b, f, distinct);
		for(pair<const int, int> & factor : f){
			distance += factor.second;
		}
		cout << (caso++) << ". " << distinct << ":" << distance << "\n";
	}
	return 0;
}