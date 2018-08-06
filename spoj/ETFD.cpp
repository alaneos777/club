#include <bits/stdc++.h>
using namespace std;

vector<int> primos;
vector<int> phi;
vector<int> ans;
vector< vector<int> > valores;

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

void cribaPhi(int n){
	phi.resize(n + 1);
	for(int i = 0; i <= n; i++) phi[i] = i;
	for(int & p : primos){
		for(int j = p; j <= n; j += p){
			phi[j] -= phi[j] / p;
		}
	}
}

void depth(int n){
	int d = 0;
	int a0 = n;
	while(a0 != 1){
		if(ans[a0] != -1){
			d += ans[a0];
			break;
		}
		a0 = phi[a0];
		d++;
	}
	ans[n] = d;
}

void calcular(int n){
	ans.resize(n + 1, -1);
	for(int i = 1; i <= n; i++){
		depth(i);
	}
	valores.resize(21);
	for(int i = 1; i <= n; i++){
		valores[ans[i]].push_back(i);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	criba(1000000);
	cribaPhi(1000000);
	calcular(1000000);
	int t;
	cin >> t;
	while(t--){
		int m, n, k, count = 0;
		cin >> m >> n >> k;
		cout << upper_bound(valores[k].begin(), valores[k].end(), n) - lower_bound(valores[k].begin(), valores[k].end(), m) << "\n";
	}
	return 0;
}